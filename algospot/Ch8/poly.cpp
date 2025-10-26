#include <bits/stdc++.h>

using namespace std;

const int MOD = 10 * 1000 * 1000;
int C, N;
int cache[101][101];

int poly(int pre, int n);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(cache, -1, sizeof(cache));

        cin >> N;
        cout << poly(0, N) << "\n";
    }

    return 0;
}

int poly(int pre, int n) {
    if (n == 0)
        return 1; // 곱셈이기 때문에 1을 return한다.

    int &ret = cache[pre][n];
    if (ret != -1)
        return ret;

    ret = 0;
    for (int use = 1; use <= n; ++use) {
        int cnt = 1;
        cnt *= poly(use, n - use);
        if (pre != 0)
            cnt *= pre + use - 1;
        ret += cnt % MOD;
        ret %= MOD;
    }

    return ret;
}