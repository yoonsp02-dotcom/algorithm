#include <bits/stdc++.h>

using namespace std;

int C;
int x[500], y[500];

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
            if (rank[a] > rank[b])
                parent[b] = a;
            else
                parent[a] = b;

            if (rank[a] == rank[b])
                rank[b]++;
        }
    }
};

double dist(int a, int b) {
    return sqrt(pow(x[a] - x[b], 2) + pow(y[a] - y[b], 2));
}

double kruskal(int n, DisjointSet &s);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; ++i)
            cin >> x[i];
        for (int i = 0; i < n; ++i)
            cin >> y[i];

        DisjointSet s(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            s.merge(a, b);
        }

        cout << fixed;
        cout.precision(10);
        cout << kruskal(n, s) << "\n";
    }

    return 0;
}

double kruskal(int n, DisjointSet &s) {
    double ret = 0.0;
    vector<pair<double, pair<int, int>>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            double d = dist(i, j);
            edges.push_back({d, {i, j}});
        }
    }
    sort(edges.begin(), edges.end());

    for (int i = 0; i < edges.size(); ++i) {
        double cost = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        if (s.find(u) == s.find(v))
            continue;
        s.merge(u, v);
        ret += cost;
    }
    return ret;
}