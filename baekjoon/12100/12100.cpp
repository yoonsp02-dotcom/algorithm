#include <bits/stdc++.h>

using namespace std;

const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {-1, 1, 0, 0};
int N;
vector<vector<int>> board;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N;
    board = vector<vector<int>> (N, vector<int>(N));
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N; ++j) 
            cin >> board[i][j];
        
    cout << game() << endl;

    return 0;
}
int& getNearestInDir(int y, int x, int dir) {
    int nextY = y + dy[dir];
    int nextX = x + dy[dir];
    while (board[nextY][nextX] == 0) {
        nextY = y + dy[dir];
        nextX = x + dy[dir];
    }
    return board[nextY][nextX];
}
void move(int dir) {
    vector<int> blank(N, -1);
    if (dir == UP) {
        for (int y = 1; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                if (board[y][x] == 0) {
                    if (blank[x] == -1) blank[x] = y;
                } else {
                    int &now = board[y][x];
                    int &nearUp = getNearestInDir(y, x, dir);
                    if (now == nearUp) {
                        board[blank[x]][x] = now + nearUp;
                        now = 0;
                        nearUp = 0;
                    } else {
                        board[blank[x]][x] = now;
                        now = 0;
                    }
                    blank[x]++;
                }
            }
        }
    } else if (dir == DOWN) {
        for (int y = N - 2; y >= 0; --y) {
            for (int x = 0; x < N; ++x) {
                if (board[y][x] == 0) {
                    if (blank[x] == -1)
                        blank[x] = y;
                } else {
                    int &now = board[y][x];
                    int &nearDown = getNearestInDir(y, x, dir);
                    if (now == nearDown) {
                        board[blank[x]][x] = now + nearDown;
                        now = 0;
                        nearDown = 0;
                    } else {
                        board[blank[x]][x] = now;
                        now = 0;
                    }
                    blank[x]++;
                }
            }
        }
    } else if (dir == RIGHT) {
        for (int x = N - 2; x >= 0; --x) {
            for (int y = 0; y < N; ++y) {
                if (board[y][x] == 0) {
                    if (blank[y] == -1)
                        blank[y] = x;
                } else {
                    int &now = board[y][x];
                    int &nearRight = getNearestInDir(y, x, dir);
                    if (now == nearRight) {
                        board[y][blank[y]] = now + nearRight;
                        now = 0;
                        nearRight = 0;
                    } else {
                        board[y][blank[y]] = now;
                        now = 0;
                    }
                    blank[y]--;
                }
            }
        }
    } else { //dir == LEFT
        for (int x = 1; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                if (board[y][x] == 0) {
                    if (blank[y] == -1)
                        blank[y] = x;
                } else {
                    int &now = board[y][x];
                    int &nearLeft = getNearestInDir(y, x, dir);
                    if (now == nearLeft) {
                        board[y][blank[y]] = now + nearLeft;
                        now = 0;
                        nearLeft = 0;
                    } else {
                        board[y][blank[y]] = now;
                        now = 0;
                    }
                    blank[y]++;
                }
            }
        }
    }
}
// 5번 이동 후 가장 큰 값 return
//bfs
int game() {
    
}