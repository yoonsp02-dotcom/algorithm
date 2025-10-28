#include <bits/stdc++.h>

using namespace std;

int C;

vector<int> getPartialMatch(const string &N);
int lenSamePrefixSuffix(const string &suffix, const string &prefix);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        string word, rev;
        cin >> word;
        rev = word;
        reverse(rev.begin(), rev.end());
        cout << 2 * word.size() - lenSamePrefixSuffix(word, rev) << "\n";
    }

    return 0;
}

vector<int> getPartialMatch(const string &N) {
    int m = N.size();
    vector<int> pi(m, 0);
    int begin = 1, matched = 0;
    while (begin + matched < m) {
        if (N[begin + matched] == N[matched]) {
            ++matched;
            pi[begin + matched - 1] = matched;
        } else {
            if (matched == 0)
                begin++;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

int lenSamePrefixSuffix(const string &suffix, const string &prefix) {
    int ret = 0, n = suffix.size();
    int begin = 0, matched = 0;
    vector<int> pi = getPartialMatch(prefix);
    while (begin + matched < n) {
        if (suffix[begin + matched] == prefix[matched]) {
            matched++;
            if (begin + matched == n)
                ret = matched;
        } else {
            if (matched == 0)
                begin++;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return ret;
}