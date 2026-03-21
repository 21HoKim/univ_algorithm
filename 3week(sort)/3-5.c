#include<stdio.h>
#include<string.h>
void sort(char arr[][101], int n, int size) {
	//n은 인덱스 기준숫자
	int N;
	int a;
	char temp[101]; //교환할때 사용
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j][n] > arr[j + 1][n]) { //n번 기준으로 정렬
				for (int k = 0; k < 100; k++) {
					temp[k] = arr[j + 1][k];
					arr[j + 1][k] = arr[j][k];
					arr[j][k] = temp[k];
				}
			}
			else if (arr[j][n] == arr[j + 1][n]) { //만약 인덱스가 같다면 사전순 정렬
				if (strcmp(arr[j], arr[j + 1]) > 0) {
					for (int k = 0; k < 100; k++) {
						temp[k] = arr[j + 1][k];
						arr[j + 1][k] = arr[j][k];
						arr[j][k] = temp[k];
					}
				}
			}
		}
	}
}
int main() {
	char arr[50][101] = { 0 }; //세로 50 가로 101
	int size_arr;
	int count = 0;
	//각 문자열 길이는 다를수있음
	char arrcut[5000] = { 0 }; //자를때 사용
	scanf("%d%*c", &size_arr); //*는 버림을 의미 줄내림\n을 버려서 버퍼를 비워주어 gets()함수 사용이 정상적으로 되게 함

	gets(arrcut); //\n개행문자가 남아있어서 버퍼를 미리 비워주어야함
	int N = strlen(arrcut);
	int n;
	scanf("%d", &n);
	char* ptr = strtok(arrcut, " "); //https://blockdmask.tistory.com/382 , 공백에 널문자를 넣고 문자를 가리키는 포인터 반환
	int i = 0;
	while (ptr != NULL)              //ptr이 NULL일때까지 (= strtok 함수가 NULL을 반환할때까지)
	{
		//printf("%s\n", ptr); //자른 문자 출력
		strcat(arr[i], ptr);
		ptr = strtok(NULL, " "); //자른 문자 다음부터 구분자 또 찾기
		i++;
	}
	sort(arr, n-1, size_arr);
	char result[5001]="";
	int len_arr = strlen(arr[0]);
	for (int i = 0; i <size_arr ; i++) {
		printf("%s ", arr[i]);
	//	strcat(result, arr[i]);
		
	}/*
	int len = strlen(result);
	char result2[5001] = "";
	int j = 0;
	for (int i = 0; i < len; i++) {
		if (i % len_arr == 0 && i!=0) {
			result2[j] = ' ';
			j++;
		}
		result2[j] = result[i];
		j++;
	}
	printf("%s", result2);*/
	return 0;
}