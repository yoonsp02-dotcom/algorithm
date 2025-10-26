#include <bits/stdc++.h>

using namespace std;

int C, N;
int cntCache[101][101];
int sumCache[101][101];
vector<vector<int>> board;

int triPathCnt(int y, int x);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(cntCache, -1, sizeof(cntCache));
        memset(sumCache, -1, sizeof(sumCache));

        cin >> N;
        board = vector<vector<int>>(N, vector<int>(N, 0));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j <= i; ++j)
                cin >> board[i][j];

        cout << triPathCnt(0, 0) << endl;
    }

    return 0;
}

int triPathSum(int y, int x) {
    if (y == N)
        return 0;

    int &ret = sumCache[y][x];
    if (ret != -1)
        return ret;

    ret = board[y][x];
    ret = max(ret, triPathSum(y + 1, x) + board[y][x]);
    ret = max(ret, triPathSum(y + 1, x + 1) + board[y][x]);

    return ret;
}

int triPathCnt(int y, int x) {
    if (y == N - 1)
        return 1;

    int &ret = cntCache[y][x];
    if (ret != -1)
        return ret;

    int sumBot = triPathSum(y + 1, x);
    int sumDia = triPathSum(y + 1, x + 1);

    if (sumDia == sumBot)
        ret = triPathCnt(y + 1, x) + triPathCnt(y + 1, x + 1);
    else if (sumDia > sumBot)
        ret = triPathCnt(y + 1, x + 1);
    else
        ret = triPathCnt(y + 1, x);

    return ret;
}