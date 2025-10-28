#include <bits/stdc++.h>

using namespace std;

int C;

vector<int> getPartialMatch(const string &N);
int kmpSearch(const string &H, const string &N);
int solve(const vector<string> &state);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int n;
        cin >> n;
        vector<string> state(n + 1);
        for (int i = 0; i <= n; ++i)
            cin >> state[i];
        cout << solve(state) << "\n";
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

int kmpSearch(const string &H, const string &N) {
    int n = H.size(), m = N.size();

    vector<int> pi = getPartialMatch(N);
    int matched = 0, begin = 0;
    while (begin + m <= n) {
        if (matched < m && H[begin + matched] == N[matched]) {
            ++matched;
            if (matched == m)
                return begin;
        } else {
            if (matched == 0)
                begin++;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return -1;
}

int solve(const vector<string> &state) {
    int ret = 0, clockWise = 1;
    for (int i = 0; i < state.size() - 1; ++i) {
        string H = state[i + 1] + state[i + 1];
        string N = state[i];
        if (!clockWise) {
            reverse(H.begin(), H.end());
            reverse(N.begin(), N.end());
        }
        ret += kmpSearch(H, N);
        clockWise = (clockWise + 1) % 2;
    }
    return ret;
}