#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;
int n, k;
int w[MAXN], v[MAXN];
int cache[MAXN][100*1000 + 1];

int maxValue(int, int);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    memset(cache, -1, sizeof(cache));
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> w[i] >> v[i];
    cout << maxValue(0, k) << "\n";

    return 0;
}

int maxValue(int stuff, int remain) {
    if (stuff >= n || remain <= 0)
        return 0;
    int& ret = cache[stuff][remain];
    if (ret != -1) 
        return ret;
    
    ret = 0;
    if (remain >= w[stuff])
        ret = v[stuff] + maxValue(stuff + 1, remain - w[stuff]);
    ret = max(ret, maxValue(stuff + 1, remain));
    return ret;
}