#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    int m = -n;
    int ans = 0;
    for (int i = 0; i < 32; ++i) {
        if ((n & (1<<i)) != (m & (1<<i))) {
            ans++;
        }
    }
    cout << ans;

    return 0;
}