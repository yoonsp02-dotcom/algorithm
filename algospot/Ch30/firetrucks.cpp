#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;
int C;
vector<pair<int, int>> adj[1001];
vector<int> firePlace, fireStation;

vector<int> fastest(int v);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int v, e, n, m;
        cin >> v >> e >> n >> m;

        for (int i = 0; i < 1001; ++i)
            adj[i].clear();
        firePlace.clear();
        fireStation.clear();
        firePlace.resize(n);
        fireStation.resize(m);

        for (int i = 0; i < e; ++i) {
            int a, b, t;
            cin >> a >> b >> t;
            adj[a].push_back({b, t});
            adj[b].push_back({a, t});
        }

        for (int i = 0; i < n; ++i)
            cin >> firePlace[i];
        for (int i = 0; i < m; ++i)
            cin >> fireStation[i];

        vector<int> d = fastest(v);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += d[firePlace[i]];
        }
        cout << ans << "\n";
    }

    return 0;
}

vector<int> fastest(int v) {
    vector<int> dist(v + 1, INF);
    priority_queue<pair<int, int>> pq;

    for (int i = 0; i < fireStation.size(); ++i) {
        pq.push({0, fireStation[i]});
        dist[fireStation[i]] = 0;
    }

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        if (cost > dist[here])
            continue;

        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            int nextCost = adj[here][i].second + cost;
            if (nextCost < dist[there]) {
                dist[there] = nextCost;
                pq.push({-nextCost, there});
            }
        }
    }
    return dist;
}