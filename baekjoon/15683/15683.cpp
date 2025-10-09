#include <bits/stdc++.h>

using namespace std;

const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};
const vector<vector<vector<int>>> cctv = {
    {},
    {{UP}, {RIGHT}, {DOWN}, {LEFT}},                        // 1
    {{UP, DOWN}, {RIGHT, LEFT}},                            // 2
    {{UP, RIGHT}, {RIGHT, DOWN}, {DOWN, LEFT}, {LEFT, UP}}, // 3
    {{LEFT, UP, RIGHT},
     {UP, RIGHT, DOWN},
     {RIGHT, DOWN, LEFT},
     {DOWN, LEFT, UP}},       // 4
    {{UP, RIGHT, DOWN, LEFT}} // 5번: 네 방향 모두
};
int N, M;
vector<vector<int>> office;

int getMinBlindSpot(vector<vector<int>> &isSurveilled,
                    vector<pair<int, int>> &cctvLoc, int here);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N >> M;
    office = vector<vector<int>>(N, vector<int>(M));
    vector<vector<int>> isSurveilled(N, vector<int>(M, 0));
    vector<pair<int, int>> cctvLoc;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            cin >> office[i][j];
            if (office[i][j] != 0 && office[i][j] != 6) {
                cctvLoc.push_back({i, j});
            }
            if (office[i][j] == 6) {
                isSurveilled[i][j] = 1;
            }
        }

    cout << getMinBlindSpot(isSurveilled, cctvLoc, 0) << "\n";

    return 0;
}
int countBlindSpot(vector<vector<int>> &isSurveilled) {
    int ret = 0;
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            if (isSurveilled[y][x] == 0)
                ret++;
        }
    }
    return ret;
}
void addSurveillArea(vector<vector<int>> &isSurveilled, int y, int x, int dir,
                     int delta) {
    while (true) {
        y += dy[dir];
        x += dx[dir];
        if (y >= N || y < 0 || x >= M || x < 0)
            break;
        if (office[y][x] == 6)
            break;
        isSurveilled[y][x] += delta;
    }
}
int getMinBlindSpot(vector<vector<int>> &isSurveilled,
                    vector<pair<int, int>> &cctvLoc, int here) {
    if (here == cctvLoc.size())
        return countBlindSpot(isSurveilled);
    int y = cctvLoc[here].first;
    int x = cctvLoc[here].second;
    int cctvNum = office[y][x];
    int ret = 100;
    for (int rot = 0; rot < cctv[cctvNum].size(); ++rot) {
        for (int i = 0; i < cctv[cctvNum][rot].size(); ++i) {
            int dir = cctv[cctvNum][rot][i];
            addSurveillArea(isSurveilled, y, x, dir, 1);
        }
        isSurveilled[y][x] += 1;
        ret = min(ret, getMinBlindSpot(isSurveilled, cctvLoc, here + 1));
        isSurveilled[y][x] += -1;
        for (int i = 0; i < cctv[cctvNum][rot].size(); ++i) {
            int dir = cctv[cctvNum][rot][i];
            addSurveillArea(isSurveilled, y, x, dir, -1);
        }
    }
    return ret;
}