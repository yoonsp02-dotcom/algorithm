#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
int C, V, M;

struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int a) {
        if (parent[a] == a)
            return a;
        return parent[a] = find(parent[a]);
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
};

vector<pair<int, pair<int, int>>> edges;
int minUpperBound(int low) {
    DisjointSet sets(V);
    for (int i = low; i < edges.size(); ++i) {
        sets.merge(edges[i].second.first, edges[i].second.second);
        if (sets.find(0) == sets.find(V - 1))
            return edges[i].first;
    }
    return INF;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        edges.clear();
        cin >> V >> M;
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({w, {u, v}});
        }
        sort(edges.begin(), edges.end());

        int ans = INF;
        for (int i = 0; i < edges.size(); ++i) {
            ans = min(minUpperBound(i) - edges[i].first, ans);
        }
        cout << ans << "\n";
    }
}