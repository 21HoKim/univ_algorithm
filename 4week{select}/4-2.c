#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 1000

void swap(int *a, int *b);
void mergeSort(int *arr, int p, int r);
int linearselect(int *arr, unsigned int p, unsigned int r, unsigned int i);
int partition(int *arr, unsigned int p, unsigned int r, int pivot_v);

int s_arr[N];
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

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, unsigned int p, unsigned int r, int pivot_v){ //p부터r까지 분할
    for(unsigned int j=p;j<=r;j++){
        if(arr[j]==pivot_v){
            swap(&arr[j],&arr[r]);
            break;
        }
    }
    int piviot=arr[r];
    
    unsigned int i=p-1;

    for(unsigned int j=p;j<=r;j++){
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

int getMedian(int *arr, int p, int r){
    int size=r-p+1;
    int m_arr[5];
    //printf("p: %d, r: %d, r-p = %d\n", p, r,r-p);
    memcpy(m_arr,&arr[p],size);
    mergeSort(m_arr,p,size-1); //부분 그룹 정렬
    return m_arr[size/2];
}

int selectPivot(int *arr, int p, int r){
    int size = r-p+1;
    if(size<=5){
        return getMedian(arr,p,r);
    }
    int n = (size+4)/5; //그룹개수
    int *arr_m = (int *)malloc(sizeof(int)*n); //중간값 저장 배열

    for(int i=0;i<n;i++){
        int gp_s = p + i*5; //그룹 시작점
        int gp_e = gp_s + 4; //그룹 끝점
        if(gp_e>r) gp_e=r; //마지막 그룹 처리

        arr_m[i]=getMedian(arr,gp_s,gp_e);
    }


    int pivot = linearselect(arr_m,0,n-1,(n+1)/2); //배열의 중간값 찾기
    free(arr_m);
    return pivot;
}

int linearselect(int *arr, unsigned int p, unsigned int r, unsigned int i){//A[p...r]에서 i번째 작은 값
    //if (p > r) return 0;
    if (i < 1 || i > (r - p + 1)) return -1;

    if(p==r) return arr[p];
    if(r-p+1<=5){//전체 원소의 수가 5개 이하이면
        mergeSort(arr,p,r);
        return arr[p+i-1];
    }
    int piviot = selectPivot(arr,p,r);
    unsigned int q=partition(arr,p,r,piviot);
    unsigned int k=q-p+1;
    if(i<k){
        return linearselect(arr,p,q-1,i);
    }
    else if(i==k){
        return arr[q];
    }
    else{
        return linearselect(arr,q+1,r,i-k); //오른쪽으로 갈 때는 반드시 i-k로 갱신
    }

}

int main(){
    int arr[N];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf(" %d",&arr[i]);
    }
    int k; //k번째로 작은 수
    scanf("%d",&k);
    
    /*
    for(int i=0;i<n;i++){
        printf("%c ",arr[i]);
    }
    printf("\nn : %d k : %d\n",n,k);
    */
    printf("%d",linearselect(arr,0,n-1,k));


    return 0;
}