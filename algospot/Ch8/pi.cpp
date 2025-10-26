#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
int c;
string pi;
int cache[10000];
int level(int idx, int len);
int minDifficulty(int idx);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> c;
    while (c--) {
        memset(cache, -1, sizeof(cache));
        pi.clear();
        cin >> pi;
        cout << minDifficulty(0) << "\n";
    }

    return 0;
}

int getLevel(int idx, int len) {
    // level 1 or 4
    bool level1Or4 = true;
    for (int i = 0; i < len - 2; ++i) {
        if (pi[idx + i] != pi[idx + i + 2])
            level1Or4 = false;
    }

    if (level1Or4) {
        if (pi[idx] == pi[idx + 1])
            return 1;
        return 4;
    }

    // level 2 or 5 or 10
    bool level2Or5 = true;
    int del = pi[idx] - pi[idx + 1];
    for (int i = 0; i < len - 1; ++i) {
        if (pi[idx + i] - pi[idx + i + 1] != del)
            level2Or5 = false;
    }

    if (level2Or5) {
        if (del == 1 || del == -1)
            return 2;
        return 5;
    }
    return 10;
}

int minDifficulty(int idx) {
    if (idx == pi.size())
        return 0;

    int &ret = cache[idx];
    if (ret != -1)
        return ret;

    ret = INF;
    for (int len = 3; len <= 5 && idx + len - 1 < pi.size(); ++len) {
        int level = getLevel(idx, len);
        ret = min(ret, level + minDifficulty(idx + len));
    }

    return ret;
}