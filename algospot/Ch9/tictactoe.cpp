#include <bits/stdc++.h>

using namespace std;

int C;
int cache[19683];

int isEnd(const vector<string> &board);
int tictactoe(vector<string> &board, char turn);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        for (int i = 0; i < 19683; ++i)
            cache[i] = -2;
        vector<string> board(3);
        int start = 0;
        for (int i = 0; i < 3; ++i) {
            cin >> board[i];
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 'x')
                    start += 1;
                else if (board[i][j] == 'o')
                    start -= 1;
            }
        }
        char turn = start ? 'o' : 'x';
        int ans = tictactoe(board, turn);
        if (ans == -1)
            cout << (char)('o' + 'x' - turn) << "\n";
        else if (ans == 1)
            cout << turn << "\n";
        else
            cout << "TIE\n";
    }

    return 0;
}

int getIdx(const vector<string> &board) {
    int ret = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ret *= 3;
            if (board[i][j] == 'x')
                ret += 1;
            else if (board[i][j] == 'o')
                ret += 2;
        }
    }
    return ret;
}

int isEnd(const vector<string> &board, char turn) {
    // 가로
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != turn)
                break;
            if (j == 2)
                return true;
        }
    }
    // 세로
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[j][i] != turn)
                break;
            if (j == 2)
                return true;
        }
    }
    // 대각선
    for (int i = 0; i < 3; ++i) {
        if (board[i][i] != turn)
            break;
        if (i == 2)
            return true;
    }
    for (int i = 0; i < 3; ++i) {
        if (board[i][2 - i] != turn)
            break;
        if (i == 2)
            return true;
    }

    return false;
}

int tictactoe(vector<string> &board, char turn) {
    if (isEnd(board, (char)('o' + 'x' - turn)))
        return -1;

    int &ret = cache[getIdx(board)];
    if (ret != -2)
        return ret;

    int tmp = 2;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '.') {
                board[i][j] = turn;
                tmp = min(tmp, tictactoe(board, (char)('o' + 'x' - turn)));
                board[i][j] = '.';
            }
        }
    }

    if (tmp == 2 || tmp == 0)
        return ret = 0;
    return ret = -tmp;
}