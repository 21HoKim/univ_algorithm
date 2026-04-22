#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct DisSetNode{
  struct DisSetNode *parent; //부모 노드 포인터
  int data;
  int rank;

}DisSetNode;

void MakeSet(DisSetNode *node, int data){
  node->parent = node; //자신을 부모로 설정 (초기에는 독립된 집합)
  node->data = data;
  node->rank = 0; //초기 랭크는 0
}

DisSetNode* Find(DisSetNode *node){
  if(node->parent == node) return node; //대표자 노드인 경우

  node->parent = Find(node->parent); //경로 압축
  return node->parent;
}

void Union(DisSetNode *node1, DisSetNode *node2){
  // node1과 node2가 속한 집합을 합침
  DisSetNode *root1 = Find(node1); //node1의 대표자 노드 찾기
  DisSetNode *root2 = Find(node2); //node2의 대표자 노드 찾기

  if(root1->rank > root2->rank){ //root1의 랭크가 더 큰 경우, root2를 root1의 자식으로 연결
    root2->parent = root1;
  }
  else if(root1->rank < root2->rank){ //root2의 랭크가 더 큰 경우, root1을 root2의 자식으로 연결
    root1->parent = root2;
  }
  else{ //랭크가 같은 경우, 하나를 다른 하나의 자식으로 연결
    root2->parent = root1;
    root1->rank++; //랭크 증가
  }
}



int connected(DisSetNode *node1, DisSetNode *node2){
  return Find(node1) == Find(node2); //node1과 node2가 같은 집합에 속하는지 확인
}


int main(){
  int N, Q; //N : 정점의 수, Q : 쿼리의 수
  scanf("%d %d", &N, &Q);

  DisSetNode *nodes = (DisSetNode*)malloc(N * sizeof(DisSetNode));
  
  for(int i=0;i<N;i++){
    MakeSet(&nodes[i], i); //각 정점에 대해 MakeSet 호출
  }

  for(int i=0;i<Q;i++){
    char query[10];
    scanf("%s", query);

    if(strcmp(query,"union") == 0){
        // union 연산 처리
        int a, b;
        scanf("%d %d", &a, &b);
        Union(&nodes[a-1], &nodes[b-1]);
    }

    if(strcmp(query,"connected") == 0){
        // connected 연산 처리
        int x, y;
        scanf("%d %d", &x, &y);

        if(connected(&nodes[x-1], &nodes[y-1])) puts("YES");
        else puts("NO");
      }

    }
    free(nodes);
    return 0;
}

