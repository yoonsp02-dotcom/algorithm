#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MAX_V = 500;
int C, V, E;
int adj[MAX_V][MAX_V];
int ans[MAX_V][MAX_V];
int t[MAX_V];

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 0; i < MAX_V; ++i) {
        for (int j = 0; j < MAX_V; ++j) {
            adj[i][j] = INF;
        }
    }
    cin >> V >> E;
    for (int i = 0; i < V; ++i)
        cin >> t[i];
    for (int i = 0; i < E; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a][b] = w;
        adj[b][a] = w;
    }

    solve();
    cin >> C;
    while (C--) {
        int s, e;
        cin >> s >> e;
        cout << ans[s][e] << "\n";
    }

    return 0;
}

void solve() {
    vector<pair<int, int>> order;
    for (int i = 0; i < V; ++i)
        order.push_back({t[i], i});
    sort(order.begin(), order.end());

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j) {
            if (i == j)
                ans[i][j] = 0;
            else
                ans[i][j] = adj[i][j];
        }

    for (int k = 0; k < V; ++k) {
        int w = order[k].second;
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j) {
                adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
                ans[i][j] = min(adj[i][w] + adj[w][i] + t[w], adj[i][j]);
            }
    }
}