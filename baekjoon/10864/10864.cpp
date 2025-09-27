#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int f[1001];
    memset(f, 0, sizeof(f));
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        f[a]++;
        f[b]++;
    }

    for (int i = 1; i <= N; ++i) {
        cout << f[i] << "\n";
    }

    return 0;
}