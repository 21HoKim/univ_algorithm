#include <stdio.h>
#include <string.h>

#define MAX 1000001

char T[MAX];
char P[MAX];
int pi[MAX];

void calcPi(char *P){
    int m = strlen(P);
    int j = 0;

    for (int i = 1; i < m; i++){
      while (j > 0 && P[i] != P[j])
        j = pi[j - 1];
      
      
      if (P[i] == P[j]){
            j++;
            pi[i] = j;
        }
    }
}

int KMP(char *T, char *P){
    int n = strlen(T);
    int m = strlen(P);

    int j = 0;
    int count = 0;

    for (int i = 0; i < n; i++){
        while (j > 0 && T[i] != P[j])
            j = pi[j - 1];

        if (T[i] == P[j]){
            if (j == m - 1){
                count++;

                // 겹치는 경우 처리
                j = pi[j];
            }
            else{
                j++;
            }
        }
    }
    return count;
}

int main(){
    scanf("%s", T);
    scanf("%s", P);

    calcPi(P);

    printf("%d\n", KMP(T, P));
    return 0;
}