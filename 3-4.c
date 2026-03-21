#include<stdio.h>
#include<stdlib.h>
int main(){
  int N;
  scanf("%d",&N);
  int *arr=(int*)malloc(sizeof(int)*N);
  for(int i=0;i<N;i++){
    scanf("%d",&arr[i]);
  }
  int n; //2차원 배열[n]*[3] 개수
  scanf("%d",&n);
  int **arr2=(int**)malloc(sizeof(int*)*n);
  for(int i=0;i<n;i++){
    *(arr2+i)=(int*)malloc(sizeof(int)*3);
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      scanf("%d",&arr2[i][j]);
    }
  }

  

  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      printf("%d ",arr2[i][j]); 
    }
  }

}