#include <bits/stdc++.h>

using namespace std;

int C, N, M;
int cache[201];
int price[20], prefer[20];

int sushi();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(cache, -1, sizeof(cache));
        cin >> N >> M;
        M /= 100;
        for (int i = 0; i < N; ++i) {
            cin >> price[i] >> prefer[i];
            price[i] /= 100;
        }
        cout << sushi() << "\n";
    }

    return 0;
}

int sushi() {
    int ret = 0;
    cache[0] = 0;
    for (int budget = 1; budget <= M; ++budget) {
        int cand = 0;
        for (int i = 0; i < N; ++i) {
            if (budget >= price[i])
                cand = max(cand, cache[(budget - price[i]) % 201] + prefer[i]);
        }
        cache[budget % 201] = cand;
        ret = max(ret, cand);
    }
    return ret;
}