#include<stdio.h>
#define N 100
int main(){
    int a[N];
    for(int i=0;i<N;i++){
        scanf("%d",&a[i]);
    }
    int tmp;
    int c=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(a[i]<a[j]){
                tmp=a[i];
                a[i]=a[j];
                a[j]=tmp;
            }
        }
    }
    for(int i=0;i<N;i++){
        printf("%d ",a[i]);
    }

    return 0;
}