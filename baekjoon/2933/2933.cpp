#include <bits/stdc++.h>

using namespace std;

int R, C;
char cave[100][100];
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};
vector<vector<char>> grounded;

void horizontalFlip();
void markGrounded();
void printCave();
int getFallDistance(const vector<pair<int, int>>& newCluster);
void dropCluster(const vector<pair<int, int>> &newCluster, int diff);
void throwStick(int h);
void startGame(vector<int>& height);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> R >> C;
    for (int y = 0; y < R; ++y) {
        string s;
        cin >> s;
        for (int x = 0; x < C; ++x) 
            cave[y][x] = s[x];
    }
    
    int n;
    cin >> n;
    vector<int> height(n);
    for (int i = 0; i < n; ++i) 
        cin >> height[i];
    startGame(height);

    // cout << "res" << endl;
    printCave();

    return 0;
}
void printCave() {
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C; ++x)
            cout << cave[y][x];
        cout << "\n";
    }
}
void horizontalFlip() {
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C / 2; ++x) {
            swap(cave[y][x], cave[y][C - x - 1]);
        }
    }
}
void markGrounded() {
    grounded.assign(R, vector<char>(C, 0));
    queue<pair<int, int>> q;

    for (int x = 0; x < C; ++x) {
        if (cave[R-1][x] == 'x' && !grounded[R-1][x]) {
            grounded[R-1][x] = 1;
            q.push({R-1, x});
        }
    }

    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();
        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= R || nx < 0 || nx >= C)
                continue;
            if (cave[ny][nx] != 'x' || grounded[ny][nx])
                continue;
            q.push({ny, nx});
            grounded[ny][nx] = 1;
        }
    }
}
vector<pair<int ,int>> collectFloating() {
    vector<pair<int, int>> floating;
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C; ++x) {
            if (cave[y][x] == 'x' && !grounded[y][x])
                floating.push_back({x, y});
        }
    }
    return floating;
}
// newCluster : {x, y} 좌표 집합
int getFallDistance(const vector<pair<int, int>> &newCluster) {
    static bool inCluster[100][100];
    memset(inCluster, 0, sizeof(inCluster));
    for (auto [x, y] : newCluster) {
        inCluster[y][x] = true;
    }

    int best = R;

    unordered_map<int, int> bottomY;
    for (auto [x, y] : newCluster) {
        if (bottomY.find(x) == bottomY.end() || y > bottomY[x]) {
            bottomY[x] = y;
        }
    }

    for (auto [x, y] : bottomY) {
        int dist = 0;
        int ny = y + 1;

        while (ny < R && (cave[ny][x] == '.' || inCluster[ny][x])) {
            dist++;
            ny++;
        }

        best = min(best, dist);
    }

    return best;
}
void dropCluster(const vector<pair<int, int>>& newCluster, int diff) {
    for (auto here : newCluster) {
        cave[here.second][here.first] = '.';
    }
    for (auto here : newCluster) {
        cave[here.second + diff][here.first] = 'x';
    }
}
void throwStick(int h) {
    int breakPointY = R - h;
    int breakPointX = -1;
    for (int i = 0; i < C; ++i) {
        if (cave[breakPointY][i] == 'x') {
            breakPointX = i;
            break;
        }
    }
    if (breakPointX == -1)
        return;
    
    cave[breakPointY][breakPointX] = '.';

    markGrounded();
    auto floating = collectFloating();
    if (floating.empty())
        return;
    
    int diff = getFallDistance(floating);
    if (diff <= 0)
        return;
    dropCluster(floating, diff);
}
void startGame(vector<int>& height) {
    for (int h : height) {
        throwStick(h);
        horizontalFlip();
    }
    if (height.size() % 2 == 1)
        horizontalFlip();
}