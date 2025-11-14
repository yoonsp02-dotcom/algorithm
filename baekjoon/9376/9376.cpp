#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

int h, w;
char jail[102][102];    // 0..h+1, 0..w+1 사용
int dist3[3][102][102]; // 각 출발점별 비용

void bfs01(int who, int sy, int sx) {
    deque<pair<int, int>> dq;
    // dist init
    for (int i = 0; i <= h + 1; ++i)
        for (int j = 0; j <= w + 1; ++j)
            dist3[who][i][j] = INF;

    dist3[who][sy][sx] = 0;
    dq.push_back({sy, sx});

    while (!dq.empty()) {
        auto [y, x] = dq.front();
        dq.pop_front();
        int d = dist3[who][y][x];

        for (int dir = 0; dir < 4; ++dir) {
            int ny = y + dy[dir], nx = x + dx[dir];
            if (ny < 0 || ny > h + 1 || nx < 0 || nx > w + 1)
                continue;
            if (jail[ny][nx] == '*')
                continue; // 벽은 불가

            int wcost = (jail[ny][nx] == '#') ? 1 : 0;
            int nd = d + wcost;
            if (dist3[who][ny][nx] > nd) {
                dist3[who][ny][nx] = nd;
                if (wcost == 0)
                    dq.push_front({ny, nx});
                else
                    dq.push_back({ny, nx});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T;
    cin >> T;
    while (T--) {
        cin >> h >> w;

        // 맵 패딩을 모두 '.'로 초기화
        for (int i = 0; i <= h + 1; ++i)
            for (int j = 0; j <= w + 1; ++j)
                jail[i][j] = '.';

        vector<pair<int, int>> prisoner;
        prisoner.reserve(2);

        // 내부 입력
        for (int i = 1; i <= h; ++i) {
            string s;
            cin >> s;
            for (int j = 1; j <= w; ++j) {
                char c = s[j - 1];
                if (c == '$') {
                    prisoner.push_back({i, j});
                    jail[i][j] = '.'; // 죄수 칸은 빈칸으로 취급
                } else {
                    jail[i][j] = c;
                }
            }
        }

        // 3번의 0-1 BFS: 밖(0,0), 죄수1, 죄수2
        bfs01(0, 0, 0);
        bfs01(1, prisoner[0].first, prisoner[0].second);
        bfs01(2, prisoner[1].first, prisoner[1].second);

        // 모든 칸에 대해 합산 후 문이면 -2 보정
        int ans = INF;
        for (int i = 0; i <= h + 1; ++i) {
            for (int j = 0; j <= w + 1; ++j) {
                if (dist3[0][i][j] == INF || dist3[1][i][j] == INF ||
                    dist3[2][i][j] == INF)
                    continue; // 도달 불가

                int sum = dist3[0][i][j] + dist3[1][i][j] + dist3[2][i][j];
                if (jail[i][j] == '#')
                    sum -= 2; // 한 번만 열면 되므로 중복 보정
                ans = min(ans, sum);
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
