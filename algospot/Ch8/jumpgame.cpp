#include <bits/stdc++.h>

using namespace std;

int c, n;
int board[100][100];
int cache[100][100];

void init() {
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            cache[i][j] = -1;
            board[i][j] = -1;
        }
    }
}
int isEnd(int y, int x);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> c;
    while (c--) {
        cin >> n;
        init();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> board[i][j];

        if (isEnd(0, 0))
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";
    }

    return 0;
}

int isEnd(int y, int x) {
    if (y >= n || x >= n)
        return 0;
    if (y == n - 1 && x == n - 1)
        return 1;

    int &ret = cache[y][x];
    if (ret != -1)
        return ret;

    int num = board[y][x];
    ret = isEnd(y + num, x) || isEnd(y, x + num);

    return ret;
}