#include <bits/stdc++.h>

using namespace std;

const int NINF = -987654321;
int C, n;
int cache[51][51];
vector<int> board;

int numberGame(int s, int e);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        for (int i = 0; i < 51; ++i)
            for (int j = 0; j < 51; ++j)
                cache[i][j] = NINF;
        cin >> n;
        board = vector<int>(n, 0);
        for (int i = 0; i < n; ++i)
            cin >> board[i];
        cout << numberGame(0, n) << "\n";
    }

    return 0;
}

int numberGame(int s, int e) {
    if (s >= e)
        return 0;
    if (e - s == 1)
        return board[s];

    int &ret = cache[s][e];
    if (ret != NINF)
        return ret;

    ret = -numberGame(s + 2, e);
    ret = max(ret, -numberGame(s, e - 2));
    ret = max(ret, board[e - 1] - numberGame(s, e - 1));
    ret = max(ret, board[s] - numberGame(s + 1, e));

    return ret;
}