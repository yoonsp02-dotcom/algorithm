#include <bits/stdc++.h>

using namespace std;

int C, N, M;
double cache[1001][1001];

double climb(int n, int m);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        // memset(cache, -1, sizeof(cache));
        for (int i = 0; i < 1001; ++i)
            for (int j = 0; j < 1001; ++j)
                cache[i][j] = -1;

        cin >> N >> M;
        cout << fixed;
        cout.precision(10);
        cout << climb(N, M) << "\n";
    }

    return 0;
}

double climb(int n, int m) {
    if (n <= 0)
        return 1.0;
    if (m == 0)
        return 0.0;

    double &ret = cache[n][m];
    if (ret > -0.5)
        return ret;

    ret = (0.75 * climb(n - 2, m - 1)) + (0.25 * climb(n - 1, m - 1));
    return ret;
}