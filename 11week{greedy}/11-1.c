#include <stdio.h>
#include <stdlib.h>

typedef struct activity {
    int s;
    int f;
    long long v;
} Act;

Act *act;
int *tmp; // 병합 정렬을 위한 임시 배열

int compare(int i, int j) {
    if (act[i].f != act[j].f) return act[i].f < act[j].f;
    return act[i].s < act[j].s;
}

void merge_sort(int *order, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    merge_sort(order, left, mid);
    merge_sort(order, mid + 1, right);

    // 병합 과정
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (compare(order[i], order[j])) tmp[k++] = order[i++];
        else tmp[k++] = order[j++];
    }
    while (i <= mid) tmp[k++] = order[i++];
    while (j <= right) tmp[k++] = order[j++];

    for (int p = left; p <= right; p++) order[p] = tmp[p];
}

int find(int *order, int i) {
    int l = 1, h = i - 1, result = 0;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (act[order[mid]].f <= act[order[i]].s) {
            result = mid;
            l = mid + 1;
        } else h = mid - 1;
    }
    return result;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    act = (Act *)malloc(sizeof(Act) * (N + 1));
    int *order = (int *)malloc(sizeof(int) * (N + 1));
    tmp = (int *)malloc(sizeof(int) * (N + 1));

    for (int i = 1; i <= N; i++) {
        scanf("%d %d %lld", &act[i].s, &act[i].f, &act[i].v);
        order[i] = i;
    }

    merge_sort(order, 1, N);

    long long *dp = (long long *)calloc(N + 1, sizeof(long long));
    for (int i = 1; i <= N; i++) {
        int prev = find(order, i);
        long long take = act[order[i]].v + dp[prev];
        long long skip = dp[i - 1];
        dp[i] = (take > skip) ? take : skip;
    }

    printf("%lld\n", dp[N]);

    free(act);
    free(order);
    free(tmp);
    free(dp);
    return 0;
}
