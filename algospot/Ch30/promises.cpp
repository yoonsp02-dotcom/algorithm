#include <bits/stdc++.h>

using namespace std;

const int MAX_V = 200;
const int INF = 987654321;
int adj[MAX_V][MAX_V];
int C, V, N, M;

void floyd();
void update(int a, int b, int c);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        for (int i = 0; i < MAX_V; ++i)
            for (int j = 0; j < MAX_V; ++j)
                adj[i][j] = INF;

        cin >> V >> M >> N;
        for (int i = 0; i < M; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            adj[a][b] = min(adj[a][b], c);
            adj[b][a] = min(adj[a][b], c);
        }
        floyd();
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            if (adj[a][b] > c)
                update(a, b, c);

            else
                ans++;
        }
        cout << ans << "\n";
    }

    return 0;
}

void floyd() {
    for (int i = 0; i < V; ++i)
        adj[i][i] = 0;

    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

void update(int a, int b, int c) {
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            adj[i][j] = min(adj[i][j], min(adj[i][a] + adj[b][j] + c,
                                           adj[i][b] + adj[a][j] + c));
}