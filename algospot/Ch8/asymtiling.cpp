#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;
int C, N;
int cache[101];

int tiling(int n);
int asymTiling(int n);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(cache, -1, sizeof(cache));
        cin >> N;
        cout << asymTiling(N) << "\n";
    }

    return 0;
}

int tiling(int n) {
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;

    int &ret = cache[n];
    if (ret != -1)
        return ret;

    ret = 0;
    ret += tiling(n - 1);
    ret %= MOD;
    ret += tiling(n - 2);
    ret %= MOD;

    return ret;
}

int asymTiling(int n) {
    if (n == 1 || n == 2)
        return 0;
    int ret = tiling(n);
    int sym = tiling(n / 2);
    if (n % 2 == 0)
        sym += tiling(n / 2 - 1);
    sym %= MOD;
    ret = ((ret + MOD) - sym) % MOD;
    return ret;
}