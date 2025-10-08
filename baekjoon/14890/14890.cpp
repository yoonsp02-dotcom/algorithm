#include <bits/stdc++.h>

using namespace std;

int N, L;
vector<vector<int>> board;

vector<vector<int>> turnLeft(vector<vector<int>> &board);
bool canPass(vector<int> path);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N >> L;
    board = vector<vector<int>>(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> board[i][j];

    int res = 0;
    for (int i = 0; i < N; ++i) {
        if (canPass(board[i])) {
            res++;
            // cout << "i: " << i << endl;
        }
    }
    board = turnLeft(board);
    // cout << "finish turn" << endl;
    for (int i = 0; i < N; ++i) {
        if (canPass(board[i])) {
            res++;
            // cout << "i: " << i << endl;
        }
    }

    cout << res << "\n";

    return 0;
}
vector<vector<int>> turnLeft(vector<vector<int>> &board) {
    vector<vector<int>> ret(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ret[i][j] = board[j][N - 1 - i];
        }
    }
    return ret;
}
bool canPass(vector<int> path) {
    vector<bool> isInstalled(path.size(), false);
    deque<int> q;
    // 항상 q.size() <= L
    for (int now = 0; now + 1 < path.size(); ++now) {
        if (q.empty() && !isInstalled[now])
            q.push_back(now);

        if (path[now] == path[now + 1]) {
            q.push_back(now + 1);
            if (q.size() > L)
                q.pop_front();
        } else if (path[now] + 1 == path[now + 1]) {
            if (q.size() < L)
                return false;
            while (!q.empty()) {
                isInstalled[q.front()] = true;
                q.pop_front();
            }
        } else if (path[now] - 1 == path[now + 1]) {
            for (int iter = 1; iter <= L; ++iter) {
                if (now + iter >= N)
                    return false;
                // 경사로를 놓을 칸들이 모두 한 칸 차이이면서 아직 설치되지 않은
                // 칸이여야 함.
                if (!(path[now + iter] == path[now] - 1 &&
                      !isInstalled[now + iter]))
                    return false;
                isInstalled[now + iter] = true;
            }
            now += L - 1;
            q.clear();
        } else {
            return false;
        }
    }
    return true;
}