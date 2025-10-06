#include <bits/stdc++.h>

const int INF = 987654321;
using namespace std;

int N;
int stat[21][21];
int getStat(const vector<int> &team);
int getDiff(const vector<int> &team1, const vector<int> &team2);
int minDiff();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            cin >> stat[i][j];

    cout << minDiff() << "\n";

    return 0;
}
int getStat(const vector<int> &team) {
    int ret = 0;
    for (int i = 0; i < team.size() - 1; ++i) {
        for (int j = i + 1; j < team.size(); ++j) {
            ret += stat[team[i]][team[j]] + stat[team[j]][team[i]];
        }
    }
    return ret;
}
int getDiff(const vector<int> &team1, const vector<int> &team2) {
    return abs(getStat(team1) - getStat(team2));
}
int minDiff() {
    int ret = INF;
    vector<int> masks(N + 1, 0);
    for (int i = N / 2 + 1; i <= N; ++i) {
        masks[i] = 1;
    }
    do {
        vector<int> team1, team2;
        for (int i = 1; i <= N; ++i) {
            if (masks[i] == 0)
                team1.push_back(i);
            else
                team2.push_back(i);
        }
        ret = min(ret, getDiff(team1, team2));
    } while (next_permutation(masks.begin() + 1, masks.end()));
    return ret;
}