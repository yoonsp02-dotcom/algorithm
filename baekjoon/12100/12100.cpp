#include <bits/stdc++.h>

using namespace std;

const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {-1, 1, 0, 0};
int N;

struct State {
    vector<vector<int>> board;
    int level;
    State(vector<vector<int>> _board, int _level) : board(_board), level(_level) {} 
};

int &getNearestInDir(const vector<vector<int>> &board, int y, int x, int dir);
void printBoard(std::vector<std::vector<int>> &board);
void move(vector<vector<int>> &board, int dir);
int getMax(const vector<vector<int>> &board);
int game(vector<vector<int>> &board);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N;
    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
        }
    }
    cout << "move UP" << endl;
    move(board, UP);
    printBoard(board);

    return 0;
}
void printBoard(std::vector<std::vector<int>> &board) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << board[i][j] << " ";
        cout << endl;
    }
}
int &getNearestInDir(vector<vector<int>> &board, int y, int x, int dir) {
    int nextY = y + dy[dir];
    int nextX = x + dx[dir];
    while (board[nextY][nextX] == 0) {
        if (nextY + dy[dir] < N && nextY + dy[dir] >= 0 &&
            nextX + dx[dir] < N && nextX + dx[dir] >= 0) {
            nextY += dy[dir];
            nextX += dx[dir];
        }
        else
            break;
    }
    return board[nextY][nextX];
}
void move(vector<vector<int>> &board, int dir) {
    vector<int> blank(N, -1);
    if (dir == UP) {
        for (int y = 0; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                if (board[y][x] == 0) {
                    if (blank[x] == -1) blank[x] = y;
                } else if (y != 0) {
                    int &now = board[y][x];
                    int &nearUp = getNearestInDir(board, y, x, dir);
                    if (now == nearUp) {
                        nearUp *= 2;
                        now = 0;
                    } else {
                        board[blank[x]][x] = now;
                        now = 0;
                        blank[x]++;
                    }
                }
            }
        }
    } else if (dir == DOWN) {
        for (int y = N - 1; y >= 0; --y) {
            for (int x = 0; x < N; ++x) {
                if (board[y][x] == 0) {
                    if (blank[x] == -1)
                        blank[x] = y;
                } else if (y != N - 1) {
                    int &now = board[y][x];
                    int &nearDown = getNearestInDir(board, y, x, dir);
                    if (now == nearDown) {
                        nearDown *= 2;
                        now = 0;
                    } else {
                        board[blank[x]][x] = now;
                        now = 0;
                        blank[x]++;
                    }
                }
            }
        }
    } else if (dir == RIGHT) {
        for (int x = N - 1; x >= 0; --x) {
            for (int y = 0; y < N; ++y) {
                if (board[y][x] == 0) {
                    if (blank[y] == -1)
                        blank[y] = x;
                } else if (x != N - 1) {
                    int &now = board[y][x];
                    int &nearRight = getNearestInDir(board, y, x, dir);
                    if (now == nearRight) {
                        nearRight *= 2;
                        now = 0;
                    } else {
                        board[y][blank[y]] = now;
                        now = 0;
                        blank[y]--;
                    }
                }
            }
        }
    } else { //dir == LEFT
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                if (board[y][x] == 0) {
                    if (blank[y] == -1)
                        blank[y] = x;
                } else if (x != 0) {
                    int &now = board[y][x];
                    int &nearLeft = getNearestInDir(board, y, x, dir);
                    if (now == nearLeft) {
                        nearLeft *= 2;
                        now = 0;
                    } else {
                        board[y][blank[y]] = now;
                        now = 0;
                        blank[y]++;
                    }
                }
            }
        }
    }
}
int getMax(const vector<vector<int>> &board) {
    int ret = 0;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            ret = max(ret, board[i][j]);
        }
    }
    return ret;
}
// 5번 이동 후 가장 큰 값 return
//bfs
int game(vector<vector<int>> &board) {
    queue<State> q;
    q.push(State(board, 0));
    int ret = 0;
    while (!q.empty()) {
        State here = q.front();
        q.pop();

        if (here.level == 5) {
            ret = max(ret, getMax(here.board));
            continue;
        }
        for (int dir = UP; dir <= LEFT; ++dir) {
            vector<vector<int>> board = here.board;
            move(board, dir);
            State there(board, here.level + 1);
            q.push(there);
        }
    }
    return ret;
}