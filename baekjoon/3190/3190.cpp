#include <bits/stdc++.h>

using namespace std;

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, 1, -1};
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
queue<pair<int, int>> snake;
bool isBody[100][100];
int board[100][100];
int N;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    memset(isBody, 0, sizeof(isBody));
    memset(board, 0, sizeof(board));
    int K;
    cin >> N >> K;
    for (int i = 0; i < K; ++i) {
        int r, c;
        cin >> r >> c;
        board[r][c] = 1;
    }
    int L;
    cin >> L;
    int res = 0;
    int dir = RIGHT;
    while (L--) {
        int sec;
        char d;
        bool isFinished = false;
        cin >> sec >> d;
        while (sec--) {
            if (move(dir)) {
                res++;
            }
            else {
                isFinished = true;
            }
        }
        if (isFinished) {
            cout << sec << endl;
            break;
        }
        if (d == 'D') {
            dir += 1;
        } else if (d == 'L') {
            dir -= 1;
        }
    }

    return 0;
}

bool move(int dir) {
    pair<int, int> head = snake.back();
    int nextY = head.first + dy[dir];
    int nextX = head.second + dx[dir];
    if (nextY >= N || nextY < 0 || nextX >= N || nextY < 0) 
        return false;
    if (isBody[nextY][nextX])
        return false;
    isBody[nextY][nextX] = true;
    pair<int, int> newHead = {nextY, nextX};
    snake.push(newHead);
    if (board[nextY][nextX] == 1)
        board[nextY][nextX] = 0;
    else
        snake.pop();
    return true;
}