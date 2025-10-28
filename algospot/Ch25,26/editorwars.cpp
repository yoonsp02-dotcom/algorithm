#include <bits/stdc++.h>

using namespace std;

int C, n, m;

struct DisjointSet {
    vector<int> parent, size, rank, enemy;
    DisjointSet(int n) : parent(n), size(n, 1), rank(n, 0), enemy(n, -1) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = find(parent[u]);
    }

    int merge(int u, int v) {
        if (u == -1 || v == -1)
            return max(u, v);
        u = find(u);
        v = find(v);
        if (u == v)
            return u;
        if (rank[u] < rank[v])
            swap(u, v);
        parent[v] = u;
        size[u] += size[v];
        if (rank[u] == rank[v])
            rank[u]++;
        return u;
    }

    bool dis(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return false;
        int a = merge(u, enemy[v]);
        int b = merge(v, enemy[u]);
        enemy[a] = b;
        enemy[b] = a;
        return true;
    }

    bool ack(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == enemy[v])
            return false;
        int a = merge(u, v);
        int b = merge(enemy[u], enemy[v]);
        enemy[a] = b;
        if (b != -1)
            enemy[b] = a;
        return true;
    }
};

int maxParty(DisjointSet &buf) {
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        if (buf.parent[i] == i) {
            int enemy = buf.enemy[i];
            if (enemy > i)
                continue;
            int enemySize = buf.size[enemy];
            int mySize = buf.size[i];
            ret += max(mySize, enemySize);
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> n >> m;
        DisjointSet buf(n);
        string comment;
        int u, v, contradict = -1;
        for (int i = 1; i <= m; ++i) {
            cin >> comment >> u >> v;
            if (contradict != -1)
                continue;

            if (comment == "ACK") {
                if (!buf.ack(u, v))
                    contradict = i;
            } else {
                if (!buf.dis(u, v))
                    contradict = i;
            }
        }
        if (contradict != -1)
            cout << "CONTRADICTION AT " << contradict << "\n";
        else
            cout << "MAX PARTY SIZE IS " << maxParty(buf) << "\n";
    }

    return 0;
}