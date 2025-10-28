#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;
int cameras;
int C, G, H;

int dfs(int here);
int installedCameras();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> G >> H;
        adj.clear();
        adj = vector<vector<int>>(G);
        for (int i = 0; i < H; ++i) {
            int s, e;
            cin >> s >> e;
            adj[s].push_back(e);
            adj[e].push_back(s);
        }
        cout << installedCameras() << "\n";
    }

    return 0;
}

int dfs(int here) {
    visited[here] = true;
    int childrenState[3] = {0};
    for (int i = 0; i < adj[here].size(); ++i) {
        int child = adj[here][i];
        if (!visited[child])
            childrenState[dfs(child)]++;
    }

    if (childrenState[UNWATCHED]) {
        cameras++;
        return INSTALLED;
    } else if (childrenState[INSTALLED])
        return WATCHED;

    return UNWATCHED;
}

int installedCameras() {
    cameras = 0;
    visited = vector<bool>(G, false);
    for (int i = 0; i < G; ++i) {
        if (!visited[i] && dfs(i) == UNWATCHED)
            cameras++;
    }
    return cameras;
}