#include <bits/stdc++.h>

using namespace std;

int N, M, safetyArea = 0;
vector<vector<int>> board;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

vector<vector<int>> spread();
int cntSafety(const vector<vector<int>> &board);
void findMaxSafety(int wall, int prevY, int prevX);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N >> M;
    board = vector<vector<int>>(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> board[i][j];
        }
    }
    findMaxSafety(3, 0, -1);

    cout << safetyArea << "\n";

    return 0;
}
vector<vector<int>> spread() {
    vector<vector<int>> spreadBoard = board;
    queue<pair<int, int>> q;
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < M; ++x)
            if (spreadBoard[y][x] == 2)
                q.push({y, x});
    
    while (!q.empty()) {
        pair<int, int> here = q.front();
        q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            int ny = here.first + dy[dir];
            int nx = here.second + dx[dir];
            if (ny >= N || ny < 0 || nx >= M || nx < 0)
                continue;
            if (spreadBoard[ny][nx] == 0) {
                spreadBoard[ny][nx] = 2;
                q.push({ny, nx});
            }
        }
    }
    return spreadBoard;
}
int cntSafety(const vector<vector<int>> &board) {
    int ret = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (board[i][j] == 0)
                ret++;
        }
    }
    return ret;
}
void findMaxSafety(int wall, int prevY, int prevX) {
    if (wall == 0) {
        vector<vector<int>> spreadBoard = spread();
        safetyArea = max(safetyArea, cntSafety(spreadBoard));
        return;
    }

    for (int x = prevX + 1; x < M; ++x) {
        if (board[prevY][x] == 0) {
            board[prevY][x] = 1;
            findMaxSafety(wall - 1, prevY, x);
            board[prevY][x] = 0;
        }
    }
    for (int y = prevY + 1; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            if (board[y][x] == 0) {
                board[y][x] = 1;
                findMaxSafety(wall - 1, y, x);
                board[y][x] = 0;
            }
        }
    }
}