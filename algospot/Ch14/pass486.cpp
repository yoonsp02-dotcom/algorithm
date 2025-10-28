#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10 * 1000 * 1000;
int C;
// minFactor[i] = i의 가장 작은 소인수
int minFactor[MAXN + 1];
// cntFactors[i] = i의 약수의 수
int cntFactors[MAXN + 1];
// minFactorPower[i] = i의 소인수 분해에 포함된 minFactor[i]의 power수
int minFactorPower[MAXN + 1];

void eratosthenes();
void getFactors();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    eratosthenes();
    getFactors();
    while (C--) {
        int n, lo, hi;
        cin >> n >> lo >> hi;
        int ans = 0;
        for (int i = lo; i <= hi; ++i) {
            if (cntFactors[i] == n)
                ans++;
        }
        cout << ans << "\n";
    }

    return 0;
}

void eratosthenes() {
    for (int i = 0; i <= MAXN; ++i)
        minFactor[i] = i;
    minFactor[0] = minFactor[1] = -1;
    int sqrtn = int(sqrt(MAXN));
    for (int i = 2; i <= sqrtn; ++i) {
        if (minFactor[i] == i) {
            for (int j = i * i; j <= MAXN; j += i)
                if (minFactor[j] == j)
                    minFactor[j] = i;
        }
    }
}

void getFactors() {
    cntFactors[1] = 1;
    for (int i = 0; i <= MAXN; ++i) {
        if (minFactor[i] == i) {
            cntFactors[i] = 2;
            minFactorPower[i] = 1;
        } else {
            int p = minFactor[i];
            int m = i / p;
            if (minFactor[m] != p)
                minFactorPower[i] = 1;
            else
                minFactorPower[i] = minFactorPower[m] + 1;
            int a = minFactorPower[i];
            cntFactors[i] = (cntFactors[m] / a) * (a + 1);
        }
    }
}