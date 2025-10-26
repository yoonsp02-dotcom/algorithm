#include <bits/stdc++.h>

using namespace std;

int c;
string wildcard;
vector<string> words;
int cache[50][100][100]; //[wordNum][wildcardIdx][wordIdx]
int matched(int wordNum, int wcIdx, int wordIdx);

void init() {
    wildcard.clear();
    words.clear();
    for (int i = 0; i < 50; ++i)
        for (int j = 0; j < 100; ++j)
            for (int k = 0; k < 100; ++k)
                cache[i][j][k] = -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> c;
    while (c--) {
        init();
        int n;
        cin >> wildcard >> n;
        words = vector<string>(n);
        for (int i = 0; i < n; ++i) {
            cin >> words[i];
        }
        sort(words.begin(), words.end());

        for (int i = 0; i < n; ++i) {
            if (matched(i, 0, 0))
                cout << words[i] << "\n";
        }
    }

    return 0;
}

int matched(int wordNum, int wcIdx, int wordIdx) {
    string w = words[wordNum];
    if (wcIdx == wildcard.size() - 1 && wildcard[wcIdx] == '*')
        return 1;
    if (wordIdx == w.size() && wcIdx == wildcard.size())
        return 1;

    int &ret = cache[wordNum][wcIdx][wordIdx];
    if (ret != -1)
        return ret;

    if (wildcard[wcIdx] == '*') {
        if (wcIdx == wildcard.size() - 1)
            return ret = 1;
        for (int skip = 0; wordIdx + skip < w.size(); ++skip) {
            if (matched(wordNum, wcIdx + 1, wordIdx + skip)) {
                return ret = 1;
            }
        }
    }

    else if (wildcard[wcIdx] == '?' || wildcard[wcIdx] == w[wordIdx])
        return ret = matched(wordNum, wcIdx + 1, wordIdx + 1);

    return ret = 0;
}