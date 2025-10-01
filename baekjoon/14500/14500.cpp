#include <bits/stdc++.h>

using namespace std;

int N, M;
int tetromino[19][4][2] = {
    // 1 1 1 1
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
    // 1 1 1
    // 1
    {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
    {{0, 0}, {0, 1}, {0, 2}, {-1, 2}},
    {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
    {{0, 0}, {0, 1}, {0, 2}, {1, 0}},
    // 1 1 1
    //     1
    {{0, 0}, {1, 0}, {2, 0}, {2, -1}},
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
    {{0, 0}, {1, 0}, {2, 0}, {0, 1}},
    {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
    //   1 1
    // 1 1
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
    {{0, 0}, {0, 1}, {1, 0}, {1, -1}},//다름
    // 1 1
    //   1 1
    {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
    {{0, 0}, {1, 0}, {1, -1}, {2, -1}},
    // 1 1 1
    //   1
    {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
    {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
    {{0, 0}, {0, 1}, {0, 2}, {-1, 1}},
    {{0, 0}, {1, 0}, {2, 0}, {1, -1}},
    // 1 1
    // 1 1
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
};

vector<vector<int>> board;

bool inRange(int type, int y, int x);
int getVal(int type, int y, int x);
int getMaxVal();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N >> M;
    board = vector<vector<int>>(N, vector<int>(M));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> board[i][j];

    cout << getMaxVal() << "\n";
    return 0;
}

bool inRange(int type, int y, int x) {
    for (int i = 0; i < 4; ++i) {
        int dy = tetromino[type][i][0];
        int dx = tetromino[type][i][1];
        if (y + dy >= N || y + dy < 0 || x + dx >= M || x + dx < 0)
            return false;
    }
    return true;
}
int getVal(int type, int y, int x) {
    int ret = 0;
    for (int i = 0; i < 4; ++i) {
        int dy = tetromino[type][i][0];
        int dx = tetromino[type][i][1];
        ret += board[y + dy][x + dx];
    }
    return ret;
}
int getMaxVal() {
    int ret = 0;
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            for (int type = 0; type < 19; ++type) {
                if (inRange(type, y, x)) {
                    int val = getVal(type, y, x);
                    ret = max(ret, val);
                }
            }
        }
    }
    return ret;
}