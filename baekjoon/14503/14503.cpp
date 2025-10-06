#include <bits/stdc++.h>

using namespace std;

const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};
vector<vector<int>> board;
vector<vector<bool>> isCleaned;
int N, M;

int startClean(int y, int x, int dir);
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    cin >> N >> M;
    int startY, startX, dir;
    cin >> startY >> startX >> dir;
    board = vector<vector<int>>(N, vector<int>(M));
    isCleaned = vector<vector<bool>>(N, vector<bool>(M, false));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> board[i][j];

    cout << startClean(startY, startX, dir) << "\n";

    return 0;
}

int startClean(int y, int x, int dir) {
    int cleaned = 0;
    if (!isCleaned[y][x]) {
        cleaned = 1;
        isCleaned[y][x] = true;
    }
    for (int i = 0; i < 4; ++i) {
        dir = (dir + 3) % 4;
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (board[ny][nx] == 0 && !isCleaned[ny][nx]) {
            cleaned += startClean(ny, nx, dir);
            return cleaned;
        }
    }
    int backY = y + dy[(dir + 2) % 4];
    int backX = x + dx[(dir + 2) % 4];
    if (board[backY][backX] == 1) {
        return cleaned;
    }
    
    return cleaned + startClean(backY, backX, dir);
}