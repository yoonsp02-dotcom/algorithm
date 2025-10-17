#include <bits/stdc++.h>

using namespace std;

struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u) {
        if (u == parent[u])
            return u;
        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return;
        if (rank[u] < rank[v])
            swap(u, v);
        parent[v] = u;
        if (rank[u] == rank[v])
            rank[u]++;
    }
};
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};
vector<string> lake;
int R, C;

int getIdx(int, int);
vector<int> melting(DisjointSet&, vector<int>&);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> R >> C;
    lake = vector<string>(R);
    vector<int> water, swan;
    DisjointSet ds(R * C);
    for (int y = 0; y < R; ++y) {
        string row;
        cin >> row;
        for (int x = 0; x < C; ++x) {
            if (row[x] == 'L') {
                swan.push_back(getIdx(y, x));
                row[x] = '.';
            }
            if (row[x] == '.') {
                water.push_back(getIdx(y, x));
                // check left
                if (x - 1 >= 0) {
                    if (row[x - 1] == '.')
                        ds.merge(getIdx(y, x), getIdx(y, x - 1));
                }
                // check up
                if (y - 1 >= 0) {
                    if (lake[y - 1][x] == '.')
                        ds.merge(getIdx(y, x), getIdx(y - 1, x));
                }
            }
        }
        lake[y] = row;
    }
    int day = 0;
    while (true) {
        if (ds.find(swan[0]) == ds.find(swan[1])) {
            break;
        }
        day++;
        water = melting(ds, water);
        for (int here : water) {
            int hereY = here / C;
            int hereX = here % C;
            for (int dir = 0; dir < 4; ++dir) {
                int ny = hereY + dy[dir];
                int nx = hereX + dx[dir];
                if (ny < 0 || ny >= R || nx < 0 || nx >= C)
                    continue;
                if (lake[ny][nx] == '.') {
                    ds.merge(here, getIdx(ny, nx));
                }
            }
        }
        // cout << "day: " << day << endl;
        // for (string s : lake) {
        //     cout << s << endl;
        // }
        // cout << endl;
    }
    cout << day << "\n";


    return 0;
}
int getIdx(int y, int x) {
    return y * C + x;
}
vector<int> melting(DisjointSet& ds, vector<int>& water) {
    vector<int> ret;
    for (int here : water) {
        int hereY = here / C;
        int hereX = here % C;
        for (int dir = 0; dir < 4; ++dir) {
            int ny = hereY + dy[dir];
            int nx = hereX + dx[dir];
            if (ny < 0 || ny >= R || nx < 0 || nx >= C) 
                continue;
            int there = getIdx(ny, nx);
            if (lake[ny][nx] == 'X') {
                lake[ny][nx] = '.';
                ds.merge(here, there);
                ret.push_back(there);
            } else if (lake[ny][nx] == '.') {
                ds.merge(here, there);
            }
        }
    }
    return ret;
}