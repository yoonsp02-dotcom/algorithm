#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};
int h, w;
vector<string> jail;
int openDoor[3][102][102];

int bfs(int, int);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<pair<int, int>> prisoner;
    int t;
    cin >> t;
    while (t--) {
        cin >> h >> w;
        for (int i = 0; i < h; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < w; ++j) {
                if (s[j] == '$') {
                    prisoner.push_back({i, j});
                    s[j] = '.';
                }
            }
            jail.push_back(s);
        }
        int door = bfs(prisoner[0].first, prisoner[0].second);
        door = max(door, bfs(prisoner[1].first, prisoner[1].second));
        cout << door << "\n";
    }

    return 0;
}

int bfs(int startY, int startX) {
    int ret = INF;
    deque<pair<pair<int, int>, int>> q; //{y, x, cost}
    vector<vector<bool>> discosvered(h, vector<bool>(w, false));
    q.push_back({{startY, startX}, 0});
    discosvered[startY][startX] = true;
    while (!q.empty()) {
        auto [y, x] = q.front().first;
        int c = q.front().second;
        q.pop_front();
        for (int dir = 0; dir < 4; ++dir){ 
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if (ny < 0 || ny >= h || nx < 0 || nx >= w) {
                ret = min(ret, c);
                continue;
            }
            if (jail[ny][nx] == '*' || discosvered[ny][nx])
                continue;
            if (jail[ny][nx] == '.') {
                q.push_front({{ny, nx}, c});
                discosvered[ny][nx] = true;
            } else {
                q.push_back({{ny, nx}, c + 1});
                jail[ny][nx] = '.';
                discosvered[ny][nx] = true;
            }
        }
    }
    return ret;
}