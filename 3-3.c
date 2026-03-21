#include<stdio.h>
int main(){
    int N;
    char arr[1000];
    char ans[1000];

    int count[1000]={0,};
    int cum_count[1000]={0,};
    scanf("%d",&N);
    int max = 0;
    for (int i=0;i<N;i++){
        scanf("%s", &arr[i]);
        //printf("arr : %c\n",arr[i]);
        count[arr[i] - 65]++;
        if(arr[i]>max)
          max=arr[i];
    }
    cum_count[0] = count[0];
    //printf("cum_count[0] : %d\n",cum_count[0]);
    for(int i=1;i<26;i++){
        cum_count[i]=cum_count[i-1]+count[i];
        //printf("cum_count[%c] : %d\n",i+65,cum_count[i]);
    }
    for(int i = N - 1; i >= 0; i--){
        int idx = arr[i] - 65;
        cum_count[idx]--; 
        ans[cum_count[idx]] = arr[i];
    }
    for(int i = 0; i < N; i++){
        printf("%c ", ans[i]);
    }
    return 0;
}