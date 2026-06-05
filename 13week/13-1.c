#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int n, m, k_limit;
// 인접 행렬 비트마스크 배열
unsigned int initial_graph[31];

// 비트 1의 개수 카운트
int popcount(unsigned int x) {
    int count = 0;
    while (x) {
        count++;
        x &= x - 1; // 가장 우측의 1을 0으로 지움
    }
    return count;
}

// DFS
bool solve(unsigned int current_graph[31], int k) {
    int u = -1, v = -1;
    
    // 남은 간선 찾기
    for (int i = 1; i <= n; i++) {
        if (current_graph[i] != 0) {
            u = i;
            for (int j = 1; j <= n; j++) {
                if (current_graph[i] & (1u << j)) {
                    v = j;
                    break;
                }
            }
            break;
        }
    }

    if (u == -1) return true;  // 모든 간선 제거 완료 (성공)
    if (k == 0) return false;  // k 소진, 간선 남음 (실패)

    // 분기 : 정점 u 포함
    unsigned int next_graph_u[31];
    for (int i = 1; i <= n; i++) next_graph_u[i] = current_graph[i];
    unsigned int u_neighbors = next_graph_u[u];
    next_graph_u[u] = 0;
    for (int i = 1; i <= n; i++) {
        if (u_neighbors & (1u << i)) next_graph_u[i] &= ~(1u << u);
    }
    if (solve(next_graph_u, k - 1)) return true;

    // 분기 : 정점 v 포함
    unsigned int next_graph_v[31];
    for (int i = 1; i <= n; i++) next_graph_v[i] = current_graph[i];
    unsigned int v_neighbors = next_graph_v[v];
    next_graph_v[v] = 0;
    for (int i = 1; i <= n; i++) {
        if (v_neighbors & (1u << i)) next_graph_v[i] &= ~(1u << v);
    }
    if (solve(next_graph_v, k - 1)) return true;

    return false;
}

// 커널화
bool kernelize_and_solve(unsigned int graph[31], int k) {
    bool changed = true;
    
    // 고차수 정점 처리
    while (changed) {
        changed = false;
        for (int i = 1; i <= n; i++) {
            int deg = popcount(graph[i]); // 정점 i의 차수
            
            // 특정 정점의 연결 간선 수가 현재 허용량 k보다 크다면 무조건 포함
            if (deg > k) {
                k--; // 허용량 1 감소
                if (k < 0) return false; // 허용량을 초과하면 즉시 실패
                
                // 정점 i를 그래프에서 논리적으로 제거
                unsigned int neighbors = graph[i];
                graph[i] = 0;
                for (int j = 1; j <= n; j++) {
                    if (neighbors & (1u << j)) {
                        graph[j] &= ~(1u << i);
                    }
                }
                changed = true; // 그래프 변경, 규칙 1 다시 검사
            }
        }
    }

    // 조기 종료
    int remaining_edges = 0;
    int max_deg = 0;
    
    for (int i = 1; i <= n; i++) {
        int deg = popcount(graph[i]);
        remaining_edges += deg;
        if (deg > max_deg) max_deg = deg;
    }
    remaining_edges /= 2;

    // 남은 k개의 정점으로 덮을 수 있는 최대 간선 수
    if (remaining_edges > k * max_deg) {
        return false;
    }

    // 커널화로 축소된 그래프를 대상으로 재귀 탐색 시작
    return solve(graph, k);
}

int main() {
    if (scanf("%d %d %d", &n, &m, &k_limit) != 3) return 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        initial_graph[u] |= (1u << v);
        initial_graph[v] |= (1u << u);
    }

    if (kernelize_and_solve(initial_graph, k_limit)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}