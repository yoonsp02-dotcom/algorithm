#include <bits/stdc++.h>

using namespace std;

const double INF = DBL_MAX;
const int MAX_N = 10000;
int C, N, M;
vector<pair<int, double>> adj[MAX_N];

double dijkstra(int s) {
    vector<double> dist(N, INF);
    priority_queue<pair<double, int>> pq;
    pq.push({-1.0, s});
    dist[s] = 1.0;
    while (!pq.empty()) {
        double cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        if (cost > dist[here])
            continue;

        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            double nextCost = adj[here][i].second * cost;
            if (nextCost < dist[there]) {
                pq.push({-nextCost, there});
                dist[there] = nextCost;
            }
        }
    }
    return dist[N - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N >> M;
        for (int i = 0; i < MAX_N; i++) {
            adj[i].clear();
        }

        for (int i = 0; i < M; ++i) {
            int s, e;
            double w;
            cin >> s >> e >> w;
            adj[s].push_back({e, w});
            adj[e].push_back({s, w});
        }

        cout << fixed;
        cout.precision(10);
        cout << dijkstra(0) << "\n";
    }

    return 0;
}