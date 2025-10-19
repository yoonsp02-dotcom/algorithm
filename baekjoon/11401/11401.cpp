#include <bits/stdc++.h>

using namespace std;

const int MOD = 1 * 1000 * 1000 * 1000 + 7;
const int MAXN = 4 * 1000 * 1000;
map<pair<int, int>, int> cache;
int N, K;

long long fastPower(long long N, long long K);
int binoCoef(int, int);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N >> K;

    cout << binoCoef(N, K) << "\n";

    return 0;
}
// calc N^K (divied and conquer)
long long fastPower(long long N, long long K) {
    if (K == 0)
        return 1;
    if (K % 2 == 1) {
        return N * fastPower(N, K-1) % MOD;
    }
    long long half = fastPower(N, K/2);
    return half * half % MOD;
}
int binoCoef(int N, int K) {
    // N! / (K!(N - K)!)
    // (N * (N-1) * ... * (N - K + 1) / K!) % MOD
    // N * (N-1) * ... * (N - K + 1) * K!^(MOD-2)
    long long tmp = 1;
    for (int i = 0; i < K; ++i) {
        tmp *= N - i;
        tmp %= MOD;
    }
    long long facK = 1;
    for (int i = 1; i <= K; ++i) {
        facK *= i;
        facK %= MOD;
    }
    long long ret = tmp * fastPower(facK, MOD - 2) % MOD;

    return ret;
}