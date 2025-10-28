#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MAX_V = 100;
int C, V;
vector<pair<int, int>> pastAdj[MAX_V];
vector<pair<int, int>> futureAdj[MAX_V];
bool reachable[MAX_V][MAX_V];

void calcReachable();
int bellmanFord(int src, vector<pair<int, int>> *adj);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(reachable, false, sizeof(reachable));
        for (int i = 0; i < MAX_V; ++i) {
            pastAdj[i].clear();
            futureAdj[i].clear();
        }
        int W;
        cin >> V >> W;
        for (int i = 0; i < W; ++i) {
            int s, e, t;
            cin >> s >> e >> t;
            pastAdj[s].push_back({e, t});
            futureAdj[s].push_back({e, -t});
            reachable[s][e] = true;
        }
        calcReachable();
        int past = bellmanFord(0, pastAdj);
        int future = bellmanFord(0, futureAdj);

        if (!reachable[0][1])
            cout << "UNREACHABLE\n";
        else {
            if (past == -INF)
                cout << "INFINITY ";
            else
                cout << past << " ";
            if (future == -INF)
                cout << "INFINITY\n";
            else
                cout << -future << "\n";
        }
    }

    return 0;
}

void calcReachable() {
    for (int i = 0; i < V; ++i) {
        reachable[i][i] = true;
    }

    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                reachable[i][j] =
                    reachable[i][j] || (reachable[i][k] && reachable[k][j]);
}

int bellmanFord(int src, vector<pair<int, int>> *adj) {
    vector<int> upper(V, INF);
    upper[src] = 0;
    for (int iter = 0; iter < V - 1; ++iter) {
        for (int here = 0; here < V; ++here) {
            for (int i = 0; i < adj[here].size(); ++i) {
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                upper[there] = min(upper[there], upper[here] + cost);
            }
        }
    }

    for (int here = 0; here < V; ++here) {
        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            int cost = adj[here][i].second;
            if (upper[there] > upper[here] + cost)
                if (reachable[src][here] && reachable[here][1])
                    return -INF;
        }
    }

    return upper[1];
}