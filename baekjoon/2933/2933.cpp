#include <bits/stdc++.h>

using namespace std;

int R, C;
char cave[100][100];
int top[100]; ///////////////////////////////이걸로 하면 안되네...
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

void horizontalFlip();
vector<pair<int, int>> findCluster(int y, int x);
int isFloated(vector<pair<int, int>> newCluster);
void dropCluster(const vector<pair<int, int>> &newCluster, int diff);
void throwStick(int h);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    memset(top, 0, sizeof(top));
    cin >> R >> C;
    for (int y = 0; y < R; ++y) {
        string s;
        cin >> s;
        for (int x = 0; x < C; ++x) {
            cave[y][x] = s[x];
            if (cave[y][x] == 'x' && top[x] == 0)
                top[x] = y;
        }
    }
    int n;
    cin >> n;
    vector<int> height(n);
    for (int i = 0; i < n; ++i) 
        cin >> height[i];
    startGame(height);

    for (int y = 0; y < R; ++y)
        for (int x = 0; x < C; ++x) 
            cout << cave[y][x];
        cout << "\n";

    return 0;
}
void horizontalFlip() {
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C / 2; ++x) {
            swap(cave[y][x], cave[y][C - x - 1]);
        }
    }
}
// return (x, y)
vector<pair<int, int>> findCluster(int y, int x) {
    vector<pair<int, int>> cluster;
    cluster.push_back({x, y});
    bool discovered[R][C] = {0};
    queue<pair<int, int>> q;
    q.push({y, x});
    discovered[y][x] = true;
    while (!q.empty()) {
        int hereY = q.front().first;
        int hereX = q.front().second;
        q.pop();
        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= R || nx < 0 || nx > C)
                continue;
            if (cave[ny][nx] == 'x' && !discovered[ny][nx]) {
                q.push({ny, nx});
                discovered[ny][nx] = true;
                cluster.push_back({nx, ny});
            }
        }
    }
    return cluster;
}
// newCluster is ordered. (x, y)
int isFloated(vector<pair<int, int>> newCluster) {
    int idx = 0;
    int diff = 1000;
    while (idx < newCluster.size()) {
        int nowX = newCluster[idx].first;
        int nowY = newCluster[idx].second;
        diff = min(diff, nowY - top[nowX]);
        while (idx < newCluster.size() && newCluster[idx].first == nowX) {
            idx++;
        }
    }
    return diff;
}
void dropCluster(const vector<pair<int, int>>& newCluster, int diff) {
    for (auto here : newCluster) {
        cave[here.second][here.first] = '.';
    }
    for (auto here : newCluster) {
        cave[here.second - diff + 1][here.first] = 'x';
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

    // breakPoint 위랑 같은 cluster였을 때
    if (breakPointY - 1 > 0 && cave[breakPointY - 1][breakPointX] == 'x') {
        vector<pair<int, int>> newCluster;
        newCluster = findCluster(breakPointY - 1, breakPointX);
        sort(newCluster.begin(), newCluster.end());
        int diff = isFloated(newCluster);
        if (diff != 0) {
            dropCluster(newCluster, diff);
        }
    }
    // breakPoint 오른쪽이랑 같은 cluster였을 때
    if (breakPointX + 1 < C && cave[breakPointY][breakPointX + 1] == 'x') {
        vector<pair<int, int>> newCluster;
        newCluster = findCluster(breakPointY, breakPointX + 1);
        sort(newCluster.begin(), newCluster.end());
        int diff = isFloated(newCluster);
        if (diff != 0) {
            dropCluster(newCluster, diff);
        }
    }
}
void startGame(vector<int>& height) {
    for (int h : height) {
        throwStick(h);
        horizontalFlip();
    }
    if (height.size() % 2 == 1)
        horizontalFlip();
}