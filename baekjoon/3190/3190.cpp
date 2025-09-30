#include <bits/stdc++.h>

using namespace std;

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
queue<pair<int, int>> snake;
bool isBody[101][101];
int board[101][101];
int N;

void init();
bool move(int dir);
int startGame(queue<pair<int, char>> &turnInfo);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    init();
    int K;
    cin >> N >> K;
    for (int i = 0; i < K; ++i) {
        int r, c;
        cin >> r >> c;
        board[r][c] = 1;
    }
    int L;
    cin >> L;
    queue<pair<int, char>> turnInfo;
    for (int i = 0; i < L; ++i) {
        int sec; char d;
        cin >> sec >> d;
        turnInfo.push({sec, d});
    }

    int res = startGame(turnInfo);
    cout << res << endl;

    return 0;
}

void init() {
    memset(isBody, 0, sizeof(isBody));
    memset(board, 0, sizeof(board));
    snake.push({1, 1});
    isBody[1][1] = true;
}
bool move(int dir) {
    pair<int, int> head = snake.back();
    int nextY = head.first + dy[dir];
    int nextX = head.second + dx[dir];
    if (nextY > N || nextY <= 0 || nextX > N || nextX <= 0) 
        return false;
    if (isBody[nextY][nextX])
        return false;
    isBody[nextY][nextX] = true;
    snake.push({nextY, nextX});
    // cout << "push newHead(y, x): " << nextY << ", " << nextX << endl;
    if (board[nextY][nextX] == 1)
        board[nextY][nextX] = 0;
    else {
        pair<int, int> tail = snake.front();
        isBody[tail.first][tail.second] = false;
        snake.pop();
    }
    return true;
}
int startGame(queue<pair<int, char>> &turnInfo) {
    int res = 0;
    int dir = RIGHT;
    while (true) {
        if (!turnInfo.empty()) {
            pair<int, char> turn = turnInfo.front();
            if (res == turn.first) {
                if (turn.second == 'D') {
                    dir = (dir + 1) % 4;
                } else {
                    dir = (dir - 1 + 4) % 4;
                }
                turnInfo.pop();
            }
        }
        if (move(dir)) {
            res++;
        } else {
            res++;
            break;
        }
    }
    return res;
}