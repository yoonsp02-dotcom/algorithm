#include <bits/stdc++.h>

using namespace std;

int C;

long long makeNextSeed(long long seed) {
    return (seed * 214013 + 2531011) % ((long long)1 << 32);
}

int ites(int k, int n);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int k, n;
        cin >> k >> n;
        cout << ites(k, n) << "\n";
    }

    return 0;
}

int ites(int k, int n) {
    long long seed = 1983;
    queue<long long> q;
    int sum = 0, ret = 0;
    for (int i = 0; i < n; ++i) {
        int nextInput = seed % 10000 + 1;
        q.push(nextInput);
        sum += nextInput;

        while (sum > k) {
            sum -= q.front();
            q.pop();
        }

        if (sum == k)
            ret++;

        seed = makeNextSeed(seed);
    }
    return ret;
}