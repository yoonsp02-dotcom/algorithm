#include <bits/stdc++.h>

using namespace std;

int C, N, D, P, T;
vector<vector<int>> adj;
vector<int> deg;
double cache[51][101];

// target마을에서 P마을까지 거꾸로 가기
// now마을에서 days일 남았을 때, days == 0일 때 now가 P마을일 확률
double prob(int now, int days);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        for (int i = 0; i < 51; ++i)
            for (int j = 0; j < 101; ++j)
                cache[i][j] = -1;

        cin >> N >> D >> P;
        adj = vector<vector<int>>(N, vector<int>(N, 0));
        deg = vector<int>(N, 0);

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                cin >> adj[i][j];
                if (adj[i][j])
                    deg[i]++;
            }

        for (int i = 0; i < deg.size(); ++i)
            cout << deg[i] << " ";
        cout << endl;

        cin >> T;
        cout << fixed;
        cout.precision(8);
        for (int i = 0; i < T; ++i) {
            int target;
            cin >> target;
            cout << prob(target, D) << "\n";
        }
        cout << "\n";
    }

    return 0;
}

// now마을에서 days일 남았을 때, days == 0일 때 now가 P마을일 확률
double prob(int now, int days) {
    if (days == 0) {
        if (now == P)
            return 1;
        return 0;
    }

    double &ret = cache[now][days];
    if (ret > -0.5)
        return ret;

    ret = 0;
    for (int prev = 0; prev < N; ++prev) {
        if (adj[now][prev]) {
            ret += prob(prev, days - 1) / deg[prev];
        }
    }

    return ret;
}