#include <bits/stdc++.h>

using namespace std;

int c, n;
int triangle[100][100];
int cache[100][100];

void init() {
    for (int i = 0; i < 100; ++i)
        for (int j = 0; j < 100; ++j) {
            triangle[i][j] = 0;
            cache[i][j] = -1;
        }
}
int findMax(int y, int x);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> c;
    while (c--) {
        init();
        cin >> n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                cin >> triangle[i][j];
            }
        }

        cout << findMax(0, 0) << "\n";
    }

    return 0;
}

int findMax(int y, int x) {
    if (y == n - 1)
        return triangle[y][x];

    int &ret = cache[y][x];
    if (ret != -1)
        return ret;

    ret = max(ret, triangle[y][x] + findMax(y + 1, x));
    ret = max(ret, triangle[y][x] + findMax(y + 1, x + 1));
    return ret;
}