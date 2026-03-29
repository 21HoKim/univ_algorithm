#include<stdio.h>
#define N 62
void swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}
char partition(char *arr, unsigned char p, unsigned char r){ //p부터r까지 분할
    char piviot = arr[r];
    //printf("piviot : %c\n",arr[r]);
    //char tempArr[N];
    //memcpy(tempArr,arr,r-p+1);
        int i=p-1;
        for(int j=p;j<=r;j++){
            if(arr[j]<piviot){
                i++;
                //printf("arr[i] : %c arr[j] : %c\n",arr[i],arr[j]);
                swap(&arr[i],&arr[j]);
                //printf("swap arr[i] : %c arr[j] : %c\n",arr[i],arr[j]);
            }
            else if(arr[j]>piviot){
                continue;
            }
        }
        swap(&arr[i+1],&arr[r]);
    return i+1;

}


char select(char *arr, unsigned char p, unsigned char r, unsigned char i){//A[p...r]에서 i번째 작은 값
    if(p==r)
        return arr[p];
    unsigned char q=partition(arr,p,r);
    int k=q-p+1;
    if(i<k){
        return select(arr,p,q-1,i);
    }
    else if(i==k){
        return arr[q];
    }
    else{
        return select(arr,q+1,r,i-k); //오른쪽으로 갈 때는 반드시 i-k로 갱신
    }
}

int main(){
    char arr[N];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf(" %c",&arr[i]);
    }
    int k; //k번째로 작은 수
    scanf("%d",&k);
    
    /*
    for(int i=0;i<n;i++){
        printf("%c ",arr[i]);
    }
    printf("\nn : %d k : %d\n",n,k);
    */
    printf("%c",select(arr,0,n-1,k));


    return 0;
}