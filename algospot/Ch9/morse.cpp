#include <bits/stdc++.h>

using namespace std;

const int M = 1 * 1000 * 1000 * 1000 + 100;
int C, n, m, k;
int bino[201][201];

void calcBino() {
    memset(bino, 0, sizeof(bino));
    for (int i = 0; i <= 200; ++i) {
        bino[i][0] = bino[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
        }
    }
}

string kth(int n, int m, int skip);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    calcBino();
    cin >> C;
    while (C--) {
        cin >> n >> m >> k;
        cout << kth(n, m, k - 1) << "\n";
    }

    return 0;
}

string kth(int n, int m, int skip) {
    if (n == 0)
        return string(m, 'o');
    if (bino[n + m - 1][n - 1] > skip) {
        return "-" + kth(n - 1, m, skip);
    }
    return "o" + kth(n, m - 1, skip - bino[n + m - 1][n - 1]);
}