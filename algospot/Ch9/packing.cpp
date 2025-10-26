#include <bits/stdc++.h>

using namespace std;

int C, N, W;
string name[101];
int weight[101];
int need[101];
int cache[1001][101];
int choice[1001];

int maxNeed(int w, int idx);
void solve(int w, int idx, vector<int> &chosen);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(cache, -1, sizeof(cache));
        memset(choice, -1, sizeof(choice));
        cin >> N >> W;
        for (int i = 0; i < N; ++i)
            cin >> name[i] >> weight[i] >> need[i];

        vector<int> chosen;
        solve(W, 0, chosen);
        cout << maxNeed(W, 0) << " " << chosen.size() << "\n";
        for (int i = 0; i < chosen.size(); ++i)
            cout << name[chosen[i]] << "\n";
    }

    return 0;
}

int maxNeed(int w, int idx) {
    if (idx == N)
        return 0;

    int &ret = cache[w][idx];
    if (ret != -1)
        return ret;

    ret = maxNeed(w, idx + 1);
    if (w - weight[idx] >= 0)
        ret = max(ret, maxNeed(w - weight[idx], idx + 1) + need[idx]);

    return ret;
}

void solve(int w, int idx, vector<int> &chosen) {
    if (idx == N)
        return;
    if (w - weight[idx] >= 0 &&
        maxNeed(w, idx) == maxNeed(w - weight[idx], idx + 1) + need[idx]) {
        chosen.push_back(idx);
        solve(w - weight[idx], idx + 1, chosen);
    } else {
        solve(w, idx + 1, chosen);
    }
}