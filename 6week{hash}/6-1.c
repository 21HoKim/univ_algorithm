#include<stdio.h>
#include<stdlib.h>
#define HASH(k, m) (((k) % (m) +(m)) % m)
typedef struct
{
    int key;
    char isEmpty; //default : 0(비어있음)
} Table;


void hash_input(Table *table, int x, int m){
    int i = HASH(x,m);
    if(!table[i].isEmpty){ //비어있다면
        table[i].key=x;
        table[i].isEmpty=1;
    }
    else{ //비어있지 않다면 (isEmpty==1)
        while(table[i].isEmpty){
            i = HASH(i+1,m);
        }
        table[i].key=x;
        table[i].isEmpty = 1;
    }
}

int search(Table *table, int k, int m, int *cnt, int i){
    (*cnt)++;
    if((*cnt) == m)
        return -1;
    if(table[i].key==k){ //해시 테이블 안에 값이 같다면
        return 0;
    }
    else{//검사를 했는데 값이 다르다면
        i = HASH(i+1,m);
        search(table, k, m, cnt, i);
    }
}

int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    Table *table = (Table *)calloc(m,sizeof(Table));
    int key;
    for(int i=0;i<n;i++){
        scanf("%d", &key);
        hash_input(table, key, m);
    }
    int k, cnt=0;
    scanf("%d",&k);
    if(search(table, k, m, &cnt, HASH(k,m))!=-1){
        printf("%d",cnt);
    }
    else{
        printf("-1");
    }
    free(table);
    return 0;
}