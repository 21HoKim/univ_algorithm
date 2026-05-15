import sys
import heapq

input = sys.stdin.readline

def solve_dijkstra():
    try:
        N, M, S, T = map(int, input().split())
    except ValueError:
        return

    graph = [[] for _ in range(N + 1)]
    
    for _ in range(M):
        line = input().split()
        if len(line) != 3 or not line[0].isdigit():
            break
        u, v, w = map(int, line)
        graph[u].append((v, w))
        
    INF = float('inf')
    distance = [(INF, INF)] * (N + 1)
    distance[S] = (0, 0)
    
    pq = [(0, 0, S)]
    
    while pq:
        current_dist, current_edges, current_node = heapq.heappop(pq)
        
        if distance[current_node] < (current_dist, current_edges):
            continue
            
        for next_node, weight in graph[current_node]:
            next_dist = current_dist + weight
            next_edges = current_edges + 1
            
            if (next_dist, next_edges) < distance[next_node]:
                distance[next_node] = (next_dist, next_edges)
                heapq.heappush(pq, (next_dist, next_edges, next_node))
                
    if distance[T][0] == INF:
        print(-1)
    else:
        print(distance[T][0])

if __name__ == "__main__":
    solve_dijkstra()