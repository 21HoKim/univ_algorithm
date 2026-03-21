#include<stdio.h>
char s_arr[1000];
void merge(char *arr,int p,int q,int r){
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


void mergeSort(char *arr, int p, int r){
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
    char arr1[2000];
    char arr[1000];
    scanf("%d",&N);
    for (int i=0;i<N*2+1;i++){
        scanf("%c",&arr1[i]);
    }
    for (int i=0;i<N;i++){
        arr[i]=arr1[i*2+1];
    }
    //printf("%s",arr);
    //return 0;
    
    /*test*/
    /*
    int N=20;
    char arr[50]={'a','c','d','e','f',
                  'n','M','Z','j','m',
                  'Q','v','E','r','A',
                  'k','l','Q','f','n'};
    */
    mergeSort(arr,0,N-1);
    //printf("-----\n");
    for(int i=0;i<N;i++){
        printf("%c ",arr[i]);
    }



    return 0;
}