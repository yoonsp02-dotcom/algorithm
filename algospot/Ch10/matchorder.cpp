#include <bits/stdc++.h>

using namespace std;

int C, N;
vector<int> R, K;

int matchOrder();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N;
        R = vector<int>(N);
        K = vector<int>(N);
        for (int i = 0; i < N; ++i)
            cin >> R[i];
        for (int i = 0; i < N; ++i)
            cin >> K[i];

        sort(R.begin(), R.end(), greater<int>());
        sort(K.begin(), K.end(), greater<int>());

        cout << matchOrder() << "\n";
    }

    return 0;
}

int matchOrder() {
    int f = 0, win = 0;
    for (int i = 0; i < N; ++i) {
        if (R[i] <= K[f]) {
            win++;
            f++;
        }
    }
    return win;
}