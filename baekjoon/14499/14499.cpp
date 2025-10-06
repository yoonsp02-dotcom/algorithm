#include <bits/stdc++.h>

using namespace std;

int dice[7];
const int RIGHT = 1;
const int LEFT = 2;
const int UP = 3;
const int DOWN = 4;
const int opposite[7] = {0, 6, 5, 4, 3, 2, 1};
const int dy[5] = {0, 0, 0, -1, 1};
const int dx[5] = {0, 1, -1, 0, 0};
vector<vector<int>> board;
int frontFaceNum = 5, bottomFaceNum = 6, rightFaceNum = 3;
int N, M, x, y, K;

void moveDice(int dir);
int roll(int dir, int &y, int &x);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    memset(dice, 0, sizeof(dice));

    cin >> N >> M >> y >> x >> K;
    board = vector<vector<int>>(N, vector<int>(M));
    for (int y = 0; y < N; ++y) 
        for (int x = 0; x < M; ++x)
            cin >> board[y][x];

    for (int i = 0; i < K; ++i) {
        int dir;
        cin >> dir;
        int res = roll(dir, y, x);
        if (res != -1)
            cout << res << "\n";
    }

    return 0;
}

void moveDice(int dir) {
    if (dir == RIGHT) {
        int tmp = rightFaceNum;
        rightFaceNum = opposite[bottomFaceNum];
        bottomFaceNum = tmp;
    } else if (dir == LEFT) {
        int tmp = bottomFaceNum;
        bottomFaceNum = opposite[rightFaceNum];
        rightFaceNum = tmp;
    } else if (dir == UP) {
        int tmp = bottomFaceNum;
        bottomFaceNum = opposite[frontFaceNum];
        frontFaceNum = tmp;
    } else if (dir == DOWN) {
        int tmp = frontFaceNum;
        frontFaceNum = opposite[bottomFaceNum];
        bottomFaceNum = tmp;
    }
}
int roll(int dir, int &y, int &x) {
    if (y + dy[dir] >= N || y + dy[dir] < 0 || x + dx[dir] >= M ||
        x + dx[dir] < 0) {
        return -1;
    }
    y += dy[dir];
    x += dx[dir];
    moveDice(dir);
    if (board[y][x] == 0) {
        board[y][x] = dice[bottomFaceNum];
    } else {
        dice[bottomFaceNum] = board[y][x];
        board[y][x] = 0;
    }
    return dice[opposite[bottomFaceNum]];
}