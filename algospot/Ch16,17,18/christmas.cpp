#include <bits/stdc++.h>

using namespace std;

int C, N, K;
vector<int> doll, psum;

int sol1();
int sol2();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N >> K;
        doll = vector<int>(N);
        psum = vector<int>(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            cin >> doll[i];
        }
        for (int i = 1; i <= N; ++i)
            psum[i] = (psum[i - 1] + doll[i - 1]) % K;

        cout << sol1() << " " << sol2() << "\n";
    }

    return 0;
}

int sol1() {
    const int MOD = 20091101;
    vector<long long> cnt(K, 0);
    for (int i = 0; i < psum.size(); ++i)
        cnt[psum[i]]++;

    int ret = 0;
    for (int i = 0; i < cnt.size(); ++i) {
        if (cnt[i] >= 2) {
            ret += (cnt[i] * (cnt[i] - 1) / 2) % MOD;
            ret %= MOD;
        }
    }
    return ret;
}

int sol2() {
    vector<int> dp(psum.size(), 0);
    vector<int> lastSeen(K, -1);
    lastSeen[0] = 0;

    for (int i = 1; i <= N; ++i) {
        dp[i] = dp[i - 1];

        if (lastSeen[psum[i]] != -1) {
            int j = lastSeen[psum[i]];
            dp[i] = max(dp[i], dp[j] + 1);
        }
        lastSeen[psum[i]] = i;
    }
    return dp[N];
}