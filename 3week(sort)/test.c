#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    
    printf("정상 접근: %d\n", arr[4]);

    // [취약점 발생] Out-of-Bounds (OOB) Write
    // 배열의 크기는 5(인덱스 0~4)이지만, 범위를 벗어난 인덱스 5에 값을 씁니다.
    arr[5] = 99; 

    printf("버그 발생 후: %d\n", arr[5]);
    
    return 0;
}