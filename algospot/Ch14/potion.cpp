#include <bits/stdc++.h>

using namespace std;

int C, n;
int oneBottleAmounts[200]; // 한 병 만들 때 들어가는 각 재료의 양 r[i]
int addedAmounts[200];     // 이미 넣은 각 재료의 양 p[i]
int r[200];                // oneBottleAmounts[i]/gcd
int ans[200];

int gcd(int a, int b);
void potion();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> oneBottleAmounts[i];
        for (int i = 0; i < n; ++i)
            cin >> addedAmounts[i];
        potion();
        for (int i = 0; i < n; ++i)
            cout << ans[i] << " ";
        cout << "\n";
    }

    return 0;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void potion() {
    // 모든 재료의 양의 최대공약수 g 계산
    int g = oneBottleAmounts[0];
    for (int i = 1; i < n; ++i)
        g = gcd(g, oneBottleAmounts[i]);

    for (int i = 0; i < n; ++i)
        r[i] = oneBottleAmounts[i] / g;

    // coef는 최소한 한 병 이상 만들기 위해 필요한 최소 배수
    int coef = g;
    for (int i = 0; i < n; ++i)
        coef = max(coef, int(ceil(double(addedAmounts[i]) / r[i])));

    for (int i = 0; i < n; ++i)
        ans[i] = r[i] * coef - addedAmounts[i];
}