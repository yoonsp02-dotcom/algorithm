#include <bits/stdc++.h>

using namespace std;

int C, board;
char cache[1 << 25];
vector<int> moves;

inline int cell(int y, int x) { return 1 << (y * 5 + x); }
char blockGame(int board);

void precalc() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            int square = cell(i, j) + cell(i, j + 1) + cell(i + 1, j) +
                         cell(i + 1, j + 1);
            moves.push_back(cell(i, j + 1) + cell(i + 1, j) +
                            cell(i + 1, j + 1));
            moves.push_back(cell(i, j) + cell(i + 1, j) + cell(i + 1, j + 1));
            moves.push_back(cell(i, j) + cell(i, j + 1) + cell(i + 1, j + 1));
            moves.push_back(cell(i, j) + cell(i, j + 1) + cell(i + 1, j));
        }
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 4; ++j) {
            moves.push_back(cell(i, j) + cell(i, j + 1));
            moves.push_back(cell(j, i) + cell(j + 1, i));
        }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    precalc();
    cin >> C;
    while (C--) {
        memset(cache, -1, sizeof(cache));
        board = 0;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                char c;
                cin >> c;
                if (c == '#')
                    board += cell(i, j);
            }
        }
        int ans = blockGame(board);
        if (ans)
            cout << "WINNING" << "\n";
        else
            cout << "LOSING" << "\n";
    }

    return 0;
}

char blockGame(int board) {
    char &ret = cache[board];
    if (ret != -1)
        return ret;

    ret = 0;
    for (int i = 0; i < moves.size(); ++i) {
        if ((board & moves[i]) == 0) {
            if (!blockGame(board | moves[i])) {
                ret = 1;
                break;
            }
        }
    }
    return ret;
}