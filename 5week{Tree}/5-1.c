#include<stdio.h>
#include<stdlib.h>

#define MAX_KEYS 6
#define MAX_CHILDREN (MAX_KEYS + 1)
#define MIN_KEYS (MAX_KEYS / 2)

typedef struct BTreeNode{
  int keys[MAX_KEYS];
  struct BTreeNode *children[MAX_CHILDREN]; //자식 포인터 배열
  int n; //현재 키 개수
  int is_leaf; //단말 노드 여부
} BTreeNode;

typedef struct BTree{
  BTreeNode *root;
} BTree;

void split_child(BTreeNode *parent, int i, BTreeNode *full_child);
void insert_non_full(BTreeNode *node, int key);

BTreeNode* create_node(int is_leaf){
  BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
  node->n = 0;
  node->is_leaf = is_leaf;
  for(int i=0;i<MAX_CHILDREN;i++){
    node->children[i] = NULL;
  }
  return node;
}


void split_child(BTreeNode *parent, int i, BTreeNode *full_child){
  BTreeNode *new_node = create_node(full_child->is_leaf);
  int mid = MIN_KEYS; //중앙 인덱스

  new_node->n = MAX_KEYS - mid -1;
  for(int j=0;j<new_node->n;j++){
    new_node->keys[j] = full_child->keys[mid + 1 + j]; //중앙 이후 키를 새 노드로 이동
  }
  if(!full_child->is_leaf){ //children 복사 (리프노드가 아닐 때)
    for(int j=0;j<=new_node->n;j++){
      new_node->children[j] = full_child->children[mid + 1 + j];
    }
  }

  full_child->n = mid; //분할된 노드의 키 개수 조정

  for(int j=parent->n;j>i;j--){
    parent->keys[j] = parent->keys[j-1];
    parent->children[j+1] = parent->children[j];
  }
  parent->keys[i] = full_child->keys[mid]; //중앙 키를 부모로 이동
  parent->children[i+1] = new_node; //새 노드를 부모의 자식으로 연결
  parent->n++; //부모 노드의 키 개수 증가

}

void insert_non_full(BTreeNode *node, int key){
  int i = node->n - 1; //현재 노드의 마지막 키 인덱스

  if(node->is_leaf){
    while(i>=0 && key < node->keys[i]){
      node->keys[i+1] = node->keys[i]; //키를 오른쪽으로 이동
      i--;
    }
    node->keys[i+1] = key; //새 키 삽입
    node->n++; //키 개수 증가
  }
  else{
    while(i>=0 && key < node->keys[i]) i--;
    i++;
    if(node->children[i]->n == MAX_KEYS){ //자식 노드가 가득 찬 경우
      split_child(node, i, node->children[i]); //자식 노드 분할
      if(key > node->keys[i]) i++; //분할 후 키 비교하여 이동
    }
    insert_non_full(node->children[i], key); //재귀적으로 자식 노드에 삽입
  }

}

void insert(BTree *tree, int key){
  BTreeNode *root = tree->root;
  if(root->n == MAX_KEYS){
    BTreeNode *new_root = create_node(0);
    new_root->children[0] = root;
    split_child(new_root, 0, root);
    insert_non_full(new_root, key);
    tree->root = new_root;
  }
  else{
    insert_non_full(root, key);
  }
}

void inorder(BTreeNode *node){
  if(node == NULL) return;

  if(node->is_leaf){
        //키 전부 한 줄에 출력
        for(int i = 0; i < node->n; i++){
            printf("%d", node->keys[i]);
            if(i < node->n - 1) printf(" ");
        }
        printf("\n");
    }
    else{
        for(int i = 0; i < node->n; i++){
            inorder(node->children[i]);
            printf("%d\n", node->keys[i]);
        }
        inorder(node->children[node->n]);
    }
}

void free_tree(BTreeNode *node){
    if(node == NULL) return;
    if(!node->is_leaf){
        for(int i = 0; i <= node->n; i++)
            free_tree(node->children[i]);
    }
    free(node);
}

int main(){
  int N;
  scanf("%d", &N);
  BTree *tree = (BTree*)malloc(sizeof(BTree));
  tree->root = create_node(1);
  int key;
  for(int i=0;i<N;i++){
    scanf("%d", &key);
    insert(tree, key);
  }
  inorder(tree->root); //중위 순회로 키 출력
  free_tree(tree->root);
  free(tree);
  return 0;
}