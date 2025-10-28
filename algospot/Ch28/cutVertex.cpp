#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<int> discovered;
vector<bool> isCutVertex;
int counter = 0;

int findCutVertex(int here, bool isRoot) {
    int ret = discovered[here] = counter++;
    int children = 0;
    for (int i = 0; i < adj[here].size(); ++i) {
        int there = adj[here][i];
        if (discovered[there] == -1) {
            int subtree = findCutVertex(there, false);
            children++;
            if (!isRoot && subtree >= discovered[here])
                isCutVertex[here] = true;
            else ret = min(ret, subtree);
        } else {
            ret = min(ret, discovered[there]);
        }
    }
    if (isRoot)
        isCutVertex[here] = (children >= 2);
    return ret;
}