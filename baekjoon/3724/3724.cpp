#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T;
    cin >> T;
    while (T--) {
        int M, N;
        cin >> M >> N;
        vector<double> logSum(M + 1, 0.0);
        vector<int> minusCnt(M + 1, 0);
        vector<bool> hasZero(M + 1, false);

        for (int i = 0; i < N; ++i) {
            for (int j = 1; j <= M; ++j) {
                long long num;
                cin >> num;
                if (num == 0) {
                    hasZero[j] = true;
                    continue;
                }
                if (num < 0) {
                    num *= -1;
                    minusCnt[j]++;
                }
                logSum[j] += log((double)num);
            }
        }

        int bestIdx = 1;
        double bestVal = -1e300;
        for (int i = 1; i <= M; ++i) {
            double val = logSum[i];
            if (hasZero[i]) val = 0;
            if (minusCnt[i] % 2 == 1) val *= -1;

            if (val > bestVal || (fabs(val - bestVal) < 1e-12 && i > bestIdx)) {
                bestVal = val;
                bestIdx = i;
            }
        }
        cout << bestIdx << "\n";
    }

    return 0;
}