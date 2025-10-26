#include <bits/stdc++.h>

using namespace std;

int C, k;
string str[16];
int cache[15][1 << 15];
int duplicate[15][15];

int duplicateCnt(int here, int next);
int restore(int here, int used); // duplicate 개수의 최댓값 return
string reconstruct(int here, int used);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(cache, -1, sizeof(cache));
        memset(duplicate, 0, sizeof(duplicate));
        cin >> k;
        for (int i = 0; i < k; ++i)
            cin >> str[i];
        while (true) {
            bool removed = false;
            for (int i = 0; i < k && !removed; ++i) {
                for (int j = 0; j < k; ++j) {
                    if (i != j && str[i].find(str[j]) != -1) {
                        str[j] = str[k - 1];
                        k--;
                        removed = true;
                    }
                }
            }
            if (!removed)
                break;
        }
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                if (i != j)
                    duplicate[i][j] = duplicateCnt(i, j);
            }
        }
        str[k] = "";

        cout << reconstruct(k, 0) << "\n";
    }

    return 0;
}

int duplicateCnt(int f, int b) {
    for (int len = min(str[f].size(), str[b].size()); len > 0; len--) {
        if (str[f].substr(str[f].size() - len) == str[b].substr(0, len))
            return len;
    }
    return 0;
}

int restore(int here, int used) {
    if (used == (1 << k) - 1)
        return 0;

    int &ret = cache[here][used];
    if (ret != -1)
        return ret;

    ret = 0;
    for (int next = 0; next < k; ++next) {
        if (used & (1 << next))
            continue;
        ret = max(ret, restore(next, used | 1 << next) + duplicate[here][next]);
    }
    return ret;
}

string reconstruct(int here, int used) {
    if (used == (1 << k) - 1)
        return "";
    for (int next = 0; next < k; ++next) {
        if (used & (1 << next))
            continue;
        int tmp = restore(next, used | (1 << next)) + duplicate[here][next];
        if (restore(here, used) == tmp)
            return str[next].substr(duplicate[here][next]) +
                   reconstruct(next, used | (1 << next));
    }
    return "!!!!ERROR!!!!";
}