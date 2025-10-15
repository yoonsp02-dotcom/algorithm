#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
int N, M, H;
vector<vector<int>> ladder;

int getMinAdd(int, int, int);
bool isRiggedGame();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N >> M >> H;
    ladder = vector<vector<int>>(H + 1, vector<int>(N + 2, 0));
    vector<int> lineCnt(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        ladder[a][b] = 1;
        lineCnt[b]++;
    }
    int res = getMinAdd(1, 1, 0);
    if (res == INF) res = -1;
    cout << res << "\n";

    return 0;
}

int getMinAdd(int nowVer, int nowHor, int added) {
    if (isRiggedGame())
        return added;
    if (added == 3)
        return INF;
    
    int ret = INF;
    for (int ver = nowVer; ver <= N; ++ ver) {
        int startHor = (ver == nowVer ? nowHor : 1);
        for (int hor = startHor; hor <= H; ++hor) {
            if (ladder[hor][ver] == 1) continue;
            if (ladder[hor][ver - 1] || ladder[hor][ver + 1]) continue;

            ladder[hor][ver] = 1;
            ret = min(ret, getMinAdd(ver, hor + 1, added + 1));
            ladder[hor][ver] = 0;
        }
    }
    return ret;
}
bool isRiggedGame() {
    for (int start = 1; start <= N; ++start) {
        int now = start;
        for (int hor = 1; hor <= H; ++hor) {
            if (ladder[hor][now]) 
                now++;
            else if (ladder[hor][now - 1])
                now--;
        }
        if (now != start) return false;
    }
    return true;
}