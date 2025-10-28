#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 12;
int C, N, K, M, L;
int prerequisite[MAXN];
int classes[10];
int cache[10][1 << MAXN];

int bitCount(int x);
int graduation(int semester, int taken);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(cache, -1, sizeof(cache));
        cin >> N >> K >> M >> L;
        for (int i = 0; i < N; ++i) {
            prerequisite[i] = 0;
            int r, s;
            cin >> r;
            while (r--) {
                cin >> s;
                prerequisite[i] |= (1 << s);
            }
        }

        for (int i = 0; i < M; ++i) {
            classes[i] = 0;
            int c, s;
            cin >> c;
            while (c--) {
                cin >> s;
                classes[i] |= (1 << s);
            }
        }

        int ans = graduation(0, 0);
        if (ans == INF)
            cout << "IMPOSSIBLE\n";
        else
            cout << ans << "\n";
    }

    return 0;
}

int bitCount(int x) {
    if (x == 0)
        return 0;
    return x % 2 + bitCount(x / 2);
}

int graduation(int semester, int taken) {
    if (bitCount(taken) >= K)
        return 0;
    if (semester == M)
        return INF;

    int &ret = cache[semester][taken];
    if (ret != -1)
        return ret;

    ret = INF;

    // 이번 학기에 들을 수 있는 과목들
    int canTake = (classes[semester] & ~taken);

    // 선수 과목을 만족하지 못한 과목은 제거
    for (int i = 0; i < N; ++i) {
        if ((canTake & (1 << i)) &&
            (prerequisite[i] & taken) != prerequisite[i])
            canTake &= ~(1 << i);
    }

    // canTake의 부분집합들을 순회하며, 들을 수 있는 조합을 모두 시도
    for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
        if (bitCount(take) > L)
            continue;
        ret = min(ret, graduation(semester + 1, taken | take) + 1);
    }
    // 아무 과목도 듣지 않고 그냥 넘어가는 경우
    ret = min(ret, graduation(semester + 1, taken));
    return ret;
}