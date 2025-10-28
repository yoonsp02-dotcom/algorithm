#include <bits/stdc++.h>

using namespace std;

int T, H, W, R, C, best, blockSize;
vector<string> board, block;
vector<vector<pair<int, int>>> rotateBlock;
int covered[10][10];

vector<string> rotate(const vector<string> &b);
void getRotate(vector<string> &block);
bool setBlock(int y, int x, const vector<pair<int, int>> &block, int delta);
int cntVoid();
void boardCover2(int placed);
int solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while (T--) {
        rotateBlock.clear();
        board.clear();
        block.clear();
        cin >> H >> W >> R >> C;
        board.resize(H);
        block.resize(R);
        for (int i = 0; i < H; ++i)
            cin >> board[i];
        for (int i = 0; i < R; ++i)
            cin >> block[i];
        getRotate(block);
        cout << solve() << "\n";
    }

    return 0;
}

vector<string> rotate(const vector<string> &b) {
    vector<string> ret(b[0].size(), string(b.size(), ' '));
    for (int i = 0; i < b.size(); ++i) {
        for (int j = 0; j < b[0].size(); ++j) {
            ret[j][b.size() - i - 1] = b[i][j];
        }
    }
    return ret;
}

void getRotate(vector<string> &block) {
    rotateBlock.clear();
    rotateBlock.resize(4);
    for (int rot = 0; rot < 4; ++rot) {
        int originX = -1, originY = -1;
        for (int y = 0; y < block.size(); ++y) {
            for (int x = 0; x < block[0].size(); ++x) {
                if (block[y][x] == '#') {
                    if (originY == -1) {
                        originY = y;
                        originX = x;
                    }
                    rotateBlock[rot].push_back(
                        make_pair(y - originY, x - originX));
                }
            }
        }
        block = rotate(block);
    }
    sort(rotateBlock.begin(), rotateBlock.end());
    rotateBlock.erase(unique(rotateBlock.begin(), rotateBlock.end()),
                      rotateBlock.end());
    blockSize = rotateBlock[0].size();
}

bool setBlock(int y, int x, const vector<pair<int, int>> &block, int delta) {
    bool canSet = true;
    for (int i = 0; i < block.size(); ++i) {
        int ny = block[i].first + y;
        int nx = block[i].second + x;
        if (ny < 0 || ny >= H || nx < 0 || nx >= W) {
            canSet = false;
            continue;
        }
        if (covered[ny][nx])
            canSet = false;
        covered[ny][nx] += delta;
    }
    return canSet;
}

int cntVoid() {
    int ret = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (covered[i][j] == 0)
                ret++;
        }
    }
    return ret;
}

void boardCover2(int placed) {
    if ((cntVoid() / blockSize) + placed <= best)
        return;

    int y = -1, x = -1;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (covered[i][j] == 0) {
                y = i;
                x = j;
                break;
            }
        }
        if (y != -1)
            break;
    }
    if (y == -1) {
        best = max(best, placed);
        return;
    }
    for (int i = 0; i < rotateBlock.size(); ++i) {
        if (setBlock(y, x, rotateBlock[i], 1))
            boardCover2(placed + 1);
        setBlock(y, x, rotateBlock[i], -1);
    }
    covered[y][x] = 1;
    boardCover2(placed);
    covered[y][x] = 0;
}

int solve() {
    best = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            covered[i][j] = (board[i][j] == '#') ? 1 : 0;
        }
    }
    boardCover2(0);
    return best;
}