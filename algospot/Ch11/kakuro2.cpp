#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;
int C, n, q;
int candidates[10][46][1024];
int board[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];
int sum[MAXN * MAXN], length[MAXN * MAXN], known[MAXN * MAXN];

int getSize();
int getSum();
void generateCandidates();
int getCandHint(int h);
int getCandCoord(int y, int x);
void put(int y, int x, int val);
void remove(int y, int x, int val);
void printSolution();
bool search();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(hint, 0, sizeof(hint));
        memset(value, 0, sizeof(value));
        memset(board, 0, sizeof(board));
        memset(sum, 0, sizeof(sum));
        memset(length, 0, sizeof(length));
        memset(known, 0, sizeof(known));

        cin >> n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> board[i][j];
            }
        }
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int y, x, dir, s;
            cin >> y >> x >> dir >> s;
            hint[y - 1][x - 1][dir] = i;
            sum[i] = s;
            int l = 0;
            if (dir == 0) { // 길이 구한느 것만 추가하기
                while (board[y - 1][x]) {
                    hint[y - 1][x][0] = i;
                    x++;
                    l++;
                }
            } else {
                while (board[y][x - 1]) {
                    hint[y][x - 1][1] = i;
                    y++;
                    l++;
                }
            }
            length[i] = l;
        }
        generateCandidates();
        search();
    }

    return 0;
}

int getSize(int mask) {
    int ret = 0;
    for (int val = 1; val <= 9; ++val) {
        if ((1 << val) & mask)
            ret++;
    }
    return ret;
}

int getSum(int mask) {
    int ret = 0;
    for (int val = 1; val <= 9; ++val) {
        if ((1 << val) & mask)
            ret += val;
    }
    return ret;
}

void generateCandidates() {
    memset(candidates, 0, sizeof(candidates));
    for (int set = 0; set < 1024; set += 2) {
        int l = getSize(set), s = getSum(set);
        int subset = set;
        while (true) {
            candidates[l][s][subset] |= (set & ~subset);
            if (subset = 0)
                break;
            subset = (subset - 1) & set;
        }
    }
}

int getCandHint(int h) { return candidates[length[h]][sum[h]][known[h]]; }

int getCandCoord(int y, int x) {
    return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

void put(int y, int x, int val) {
    for (int h = 0; h < 2; ++h)
        known[hint[y][x][h]] += (1 << val);
    value[y][x] = val;
}

void remove(int y, int x, int val) {
    for (int h = 0; h < 2; ++h)
        known[hint[y][x][h]] -= (1 << val);
    value[y][x] = 0;
}

void printSolution() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << value[i][j] << " ";
        cout << "\n";
    }
}

bool search() {
    int y = -1, x = -1, minCands = 1023;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == 1 && value[i][j] == 0) {
                int cands = getCandCoord(i, j);
                if (getSize(minCands) > getSize(cands)) {
                    minCands = cands;
                    y = i;
                    x = j;
                }
            }

    if (minCands == 0)
        return false;
    if (y == -1) {
        printSolution();
        return true;
    }

    for (int val = 1; val < 10; val++)
        if (minCands & (1 << val)) {
            put(y, x, val);
            if (search())
                return true;
            remove(y, x, val);
        }
    return false;
}