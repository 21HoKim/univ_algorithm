#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int s_arr[1000];
void merge(int *arr,int p,int q,int r){
    int i = p;
    int j = q + 1;
    int k = p;

    while(i<=q && j<=r){
        if(arr[i]<=arr[j]){
            s_arr[k++] = arr[i++];
        }
        else{
            s_arr[k++] = arr[j++];
        }
    }

    if(i>q){
        for(int l=j;l<=r;l++){
            s_arr[k++]=arr[l];
        }
    }
    else{
        for(int l=i;l<=q;l++){
            s_arr[k++]=arr[l];
        }
    }

    for(int l=p;l<=r;l++){
        arr[l]=s_arr[l];
    }
}


void mergeSort(int *arr, int p, int r){
    int q;
    if(p<r){
        q=(p+r)/2;
        mergeSort(arr,p,q);
        mergeSort(arr,q+1,r);
        merge(arr,p,q,r);
    }
}



int main(){
  int N;
  scanf("%d",&N);
  int *arr=(int*)malloc(sizeof(int)*N); //원본 배열
  int *s_arr=(int*)malloc(sizeof(int)*N); //정답 배열
  for(int i=0;i<N;i++){
    scanf("%d",&arr[i]);
  }
  memcpy(s_arr,arr,sizeof(int)*N); //정렬 배열


  int n; //2차원 배열[n]*[3] 개수
  scanf("%d",&n);
  int *answer=(int*)malloc(sizeof(int)*n); //정답 배열
  int **arr2=(int**)malloc(sizeof(int*)*n); //정렬 기준 배열
  for(int i=0;i<n;i++){
    *(arr2+i)=(int*)malloc(sizeof(int)*3);
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<3;j++){
      scanf("%d",&arr2[i][j]);
    }
  }

//입력 종료 (입력값 검증 완료)

  for(int i=0;i<n;i++){
      mergeSort(s_arr, arr2[i][0]-1, arr2[i][1]-1);
      answer[i]=s_arr[arr2[i][2]-1+arr2[i][0]-1];
      memcpy(s_arr,arr,sizeof(int)*N); //정렬 배열 초기화
  }

  for(int i=0;i<n;i++){
    printf("%d ",answer[i]);
  }
  free(arr);
  free(s_arr);
  for(int i=0;i<n;i++){
    free(arr2[i]);
  }
  free(arr2);
  free(answer);
  return 0;
}