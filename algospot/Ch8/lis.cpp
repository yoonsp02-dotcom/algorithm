#include <bits/stdc++.h>

using namespace std;

int c, n;
int cache[501];
int sequence[501];

int lis(int idx);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> c;
    while (c--) {
        for (int i = 0; i < 501; ++i) {
            cache[i] = -1;
            sequence[i] = 0;
        }

        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> sequence[i + 1];
        }
        sequence[0] = 0;

        cout << lis(-1) - 1 << "\n";
    }

    return 0;
}

int lis(int idx) {
    int &ret = cache[idx + 1];
    if (ret != -1)
        return ret;

    ret = 1;
    for (int i = idx; i < n; ++i) {
        if (sequence[i + 1] > sequence[idx + 1]) {
            ret = max(ret, 1 + lis(i));
        }
    }

    return ret;
}