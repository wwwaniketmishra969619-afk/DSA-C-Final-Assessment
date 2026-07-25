#include <stdio.h>
#include <stdlib.h>

#define INF 1000000

void dijkstra(int n, int cost[100][100], int S, int D) {
    int dist[100];
    int visited[100];
    int parent[100];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[S] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        int min_d = INF;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min_d) {
                min_d = dist[i];
                u = i;
            }
        }

        if (u == -1 || dist[u] == INF) break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (cost[u][v] != INF && !visited[v]) {
                if (dist[u] + cost[u][v] < dist[v]) {
                    dist[v] = dist[u] + cost[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    if (dist[D] == INF) {
        printf("UNREACHABLE\n");
        return;
    }

    printf("%d\n", dist[D]);

    int path[100];
    int path_len = 0;
    int curr = D;

    while (curr != -1) {
        path[path_len++] = curr;
        curr = parent[curr];
    }

    for (int i = path_len - 1; i >= 0; i--) {
        printf("%d%c", path[i], (i == 0) ? '\n' : ' ');
    }
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    int cost[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = INF;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        cost[u][v] = w;
    }

    int S, D;
    scanf("%d %d", &S, &D);

    dijkstra(n, cost, S, D);

    return 0;
}