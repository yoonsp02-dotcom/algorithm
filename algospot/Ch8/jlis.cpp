#include <bits/stdc++.h>

using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int c, n, m;
vector<int> se1, se2;
int cache[101][101];
int jlis(int idx1, int idx2);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> c;
    while (c--) {
        for (int i = 0; i < 101; ++i)
            for (int j = 0; j < 101; ++j)
                cache[i][j] = -1;

        cin >> n >> m;
        se1 = vector<int>(n, -1);
        se2 = vector<int>(m, -1);

        for (int i = 0; i < n; ++i)
            cin >> se1[i];
        for (int i = 0; i < m; ++i)
            cin >> se2[i];

        cout << jlis(-1, -1) - 2 << "\n";
    }

    return 0;
}

int jlis(int idx1, int idx2) {
    int &ret = cache[idx1 + 1][idx2 + 1];
    if (ret != -1)
        return ret;

    ret = 2;
    long long a = ((idx1 == -1) ? NEGINF : se1[idx1]);
    long long b = ((idx2 == -1) ? NEGINF : se2[idx2]);
    long long maxElement = max(a, b);

    for (int next = idx1 + 1; next < se1.size(); ++next)
        if (se1[next] > maxElement)
            ret = max(ret, jlis(next, idx2) + 1);
    for (int next = idx2 + 1; next < se2.size(); ++next)
        if (se2[next] > maxElement)
            ret = max(ret, jlis(idx1, next) + 1);

    return ret;
}