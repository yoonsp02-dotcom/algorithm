#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;

int N, M, whole;
char board[10][10];


void checkBlocked(int ry, int rx, int by, int bx, int dir, bool& rIsBlocked,
               bool& bIsBlocked);
void moveBall(int &y, int &x, int dir, bool isBlocked);
bool move(int& rIdx, int& bIdx, int dir);
int escape(int rIdx, int bIdx);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int rIdx, bIdx;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 'O') 
                whole = 10*i + j;
            else if (board[i][j] == 'B') {
                bIdx = 10*i + j;
                board[i][j] = '.';
            }
            else if (board[i][j] == 'R') {
                rIdx = 10 * i + j;
                board[i][j] = '.';
            }
        }
    }
    
    int ans = escape(rIdx, bIdx);
    if (ans == INF) ans = -1;
    cout << ans << "\n";

    return 0;
}

void checkBlocked(int ry, int rx, int by, int bx, int dir, bool &rIsBlocked,
                  bool &bIsBlocked) {
    if (dir == UP) {
        if (rx == bx) {
            bool change = false;
            if (ry < by) {
                change = true;
                swap(ry, by);
            }
            for (int y = by + 1; y < ry; ++y) {
                if (board[y][rx] == '#') {
                    rIsBlocked = false;
                    bIsBlocked = false;
                    return;
                }
            }
            if (change) {
                rIsBlocked = false;
                bIsBlocked = true;
            } else {
                rIsBlocked = true;
                bIsBlocked = false;
            }
        } else {
            rIsBlocked = false;
            bIsBlocked = false;
        }
    } else if (dir == DOWN) {
        if (rx == bx) {
            bool change = false;
            if (ry < by) {
                change = true;
                swap(ry, by);
            }
            for (int y = by + 1; y < ry; ++y) {
                if (board[y][rx] == '#') {
                    rIsBlocked = false;
                    bIsBlocked = false;
                    return;
                }
            }
            if (change) {
                rIsBlocked = true;
                bIsBlocked = false;
            } else {
                rIsBlocked = false;
                bIsBlocked = true;
            }
        } else {
            rIsBlocked = false;
            bIsBlocked = false;
        }
    } else if (dir == RIGHT) {
        if (ry == by) {
            bool change = false;
            if (rx < bx) {
                change = true;
                swap(rx, bx);
            }
            for (int x = bx + 1; x < rx; ++x) {
                if (board[ry][x] == '#') {
                    rIsBlocked = false;
                    bIsBlocked = false;
                    return;
                }
            }
            if (change) {
                rIsBlocked = true;
                bIsBlocked = false;
            } else {
                rIsBlocked = false;
                bIsBlocked = true;
            }
        } else {
            rIsBlocked = false;
            bIsBlocked = false;
        }
    } else { // dir == LEFT
        if (ry == by) {
            bool change = false;
            if (rx < bx) {
                change = true;
                swap(rx, bx);
            }
            for (int x = bx + 1; x < rx; ++x) {
                if (board[ry][x] == '#') {
                    rIsBlocked = false;
                    bIsBlocked = false;
                    return;
                }
            }
            if (change) {
                rIsBlocked = false;
                bIsBlocked = true;
            } else {
                rIsBlocked = true;
                bIsBlocked = false;
            }
        } else {
            rIsBlocked = false;
            bIsBlocked = false;
        }
    }
}

void moveBall(int& y, int& x, int dir, bool isBlocked) {
    if (dir == UP) {
        while (y > 0) {
            if (board[y - 1][x] == '.')
                y--;
            else if (board[y - 1][x] == 'O') {
                y--;
                return;
            } else if (board[y - 1][x] == '#')
                break;
        }
        if (isBlocked) y++;
    } else if (dir == DOWN) {
        while (y < N - 1) {
            if (board[y + 1][x] == '.')
                y++;
            else if (board[y + 1][x] == 'O') {
                y++;
                return;
            } else if (board[y + 1][x] == '#')
                break;
        }
        if (isBlocked)
            y--;
    } else if (dir == RIGHT) {
        while (x < M - 1) {
            if (board[y][x + 1] == '.')
                x++;
            else if (board[y][x + 1] == 'O') {
                x++;
                return;
            } else if (board[y][x + 1] == '#')
                break;
        }
        if (isBlocked)
            x--;
    } else { // dir == LEFT
        while (x > 0) {
            if (board[y][x - 1] == '.')
                x--;
            else if (board[y][x - 1] == 'O') {
                x--;
                return;
            } else if (board[y][x - 1] == '#')
                break;
        }
        if (isBlocked)
            x++;
    }
}
// 움직여도 똑같으면 false
bool move(int &rIdx, int &bIdx, int dir) {
    int ry = rIdx / 10; int rx = rIdx % 10;
    int by = bIdx / 10; int bx = bIdx % 10;
    
    bool rIsBlocked, bIsBlocked;
    checkBlocked(ry, rx, by, bx, dir, rIsBlocked, bIsBlocked);

    moveBall(ry, rx, dir, rIsBlocked);
    moveBall(by, bx, dir, bIsBlocked);

    if ((rIdx == 10 * ry + rx) && (bIdx == 10 * by + bx))
        return false;
    rIdx = 10 * ry + rx;
    bIdx = 10 * by + bx;
    return true;
}
int escape(int rIdx, int bIdx) {
    queue<pair<int, pair<int, int>>> q; //level, rIdx, bIdx
    bool discovered[100][100];
    for (int i = 0; i < 100; ++i)
        for (int j = 0; j < 100; ++j)
            discovered[i][j] = false;
    
    q.push({0, {rIdx, bIdx}});
    discovered[rIdx][bIdx] = true;
    int ret = INF;
    while (!q.empty()) {
        int level = q.front().first;
        int hereRIdx = q.front().second.first;
        int hereBIdx = q.front().second.second;
        q.pop();
        if (level > 10) continue;

        if (hereBIdx == whole) continue;
        else if (hereRIdx == whole) {
            ret = level;
            break;
        }

        for (int dir = UP; dir <= LEFT; ++dir) {
            int newRIdx = hereRIdx;
            int newBIdx = hereBIdx;
            if (move(newRIdx, newBIdx, dir)) {
                if (!discovered[newRIdx][newBIdx]) {
                    q.push({level + 1, {newRIdx, newBIdx}});
                    discovered[newRIdx][newBIdx] = true;
                }
            }
        }
    }
    return ret;
}