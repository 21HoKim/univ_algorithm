#include<stdio.h>
#include<stdlib.h>

int main(){
    int N, W;
    scanf("%d %d", &N, &W);
    
    int *dp = (int *)calloc(W+1,sizeof(int));

    for(int i=0; i<N; i++){
        int w;
        int v;
        scanf("%d %d", &w, &v);
        for(int j=W; j>=w; j--){
            if(dp[j] < dp[j-w]+v)
                dp[j] = dp[j-w]+v;
        }
    }

    printf("%d\n",dp[W]);
    free(dp);
    return 0;
}