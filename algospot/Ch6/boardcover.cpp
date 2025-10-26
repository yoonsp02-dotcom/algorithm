#include <bits/stdc++.h>

using namespace std;

int c, h, w;
int block[4][3][2] = {{{0, 0}, {1, 0}, {1, 1}},
                      {{0, 0}, {1, 0}, {1, -1}},
                      {{0, 0}, {0, 1}, {1, 1}},
                      {{0, 0}, {0, 1}, {1, 0}}};

bool setBlock(vector<vector<int>> &board, int type, int y, int x, int delta);
int blockCover(vector<vector<int>> &board);

int main() {
    cin >> c;

    while (c--) {
        cin >> h >> w;
        vector<vector<int>> board(h, vector<int>(w));
        int cnt0 = 0;
        for (int i = 0; i < h; ++i) {
            string input;
            cin >> input;
            for (int j = 0; j < w; ++j) {
                if (input[j] == '#')
                    board[i][j] = 1;
                else {
                    board[i][j] = 0;
                    cnt0++;
                }
            }
        }

        if (cnt0 % 3 != 0) {
            cout << 0 << "\n";
            continue;
        }

        cout << blockCover(board) << "\n";
    }

    return 0;
}

bool setBlock(vector<vector<int>> &board, int type, int y, int x, int delta) {
    // cout << "type: " << type << ", (" << y << "," << x << ") delta: " <<
    // delta << endl;
    bool canSet = true;
    for (int i = 0; i < 3; ++i) {
        int ny = y + block[type][i][0];
        int nx = x + block[type][i][1];

        if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
            board[ny][nx] += delta;
            if (board[ny][nx] > 1) {
                canSet = false;
            }
        } else {
            canSet = false;
        }
    }

    return canSet;
}

// board에서 블록을 다 채울 수 있는 경우의 수를 return
int blockCover(vector<vector<int>> &board) {
    int y = -1, x = -1;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j)
            if (board[i][j] == 0) {
                y = i;
                x = j;
                break;
            }
        if (y != -1)
            break;
    }
    if (y == -1)
        return 1;

    int ret = 0;
    for (int type = 0; type < 4; ++type) {
        if (setBlock(board, type, y, x, 1)) {
            ret += blockCover(board);
        }
        setBlock(board, type, y, x, -1);
    }

    return ret;
}