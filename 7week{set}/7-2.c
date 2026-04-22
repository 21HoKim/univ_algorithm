//해시 맵으로 최빈 문자열 찾기
#include<stdio.h>
#include<string.h>

#define MAX 200000
#define TABLE_SIZE 200003
#define MAX_LEN 21

typedef struct HashNode{
  char str[MAX_LEN]; //문자열 저장
  int count; //빈도 수
  struct HashNode *next; //충돌 해결을 위한 연결 리스트
} HashNode;

//동적 할당을 피하기 위해 배열 사용
HashNode *hash_table[TABLE_SIZE]; //해시 테이블 (0으로 초기화)
HashNode nodeArr[MAX]; //노드 배열
int nodeCount = 0; //노드 배열에서 사용된 노드 수

// 최빈값 추적을 위한 변수
int maxFreq = 0; //최대 빈도수
char bestStr[MAX_LEN]; //최빈값 중 사전순으로 가장 작은 문자열

unsigned long djb2_hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % TABLE_SIZE;
}

void insert(const char *str){
  unsigned long idx = djb2_hash((unsigned char *)str);
  HashNode *node = hash_table[idx];

  //해시 충돌 처리
  while(node){ //node가 0(NULL)이 아닐 때
    if(strcmp(node->str, str) == 0){//같은 문자열일 때
      node->count++;
      if (node->count > maxFreq){ //최빈값 갱신
        maxFreq = node->count;
        strcpy(bestStr, node->str);
      }
      else if(node->count == maxFreq){ //최빈값이 같을 때 사전순 비교
        if(strcmp(node->str, bestStr) < 0){
          strcpy(bestStr, node->str);
        }
      }
      return;
    }
    node = node->next;
  }

  //새 노드 생성
  HashNode *newNode = &nodeArr[nodeCount++];
  strcpy(newNode->str, str);
  newNode->count = 1;

  //맨 앞에 새 노드 삽입
  newNode->next = hash_table[idx]; //초기엔 Null, 기존 노드 존재 시 연결
  hash_table[idx] = newNode;

  //첫 입력 또는 빈도수가 1인 상태에서 사전순 비교
  if(maxFreq == 0){
    maxFreq = 1;
    strcpy(bestStr, newNode->str);
  }
  else if(maxFreq == 1){
    if(strcmp(newNode->str, bestStr) < 0){
      strcpy(bestStr, newNode->str);
    }
  }
}

int main() {
    int n;
    scanf("%d", &n);

    char input[MAX_LEN];
    for (int i = 0; i < n; i++) {
        scanf("%s", input);
        insert(input);
    }

    printf("%s\n", bestStr);

    return 0;
}