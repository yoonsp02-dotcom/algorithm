#include <bits/stdc++.h>

using namespace std;

vector<int> getPartialMatch(const string &N);

int main() {
    string father, mother;
    cin >> father >> mother;

    vector<int> pi = getPartialMatch(father + mother);
    vector<int> ans;
    ans.push_back((father + mother).size());
    while (true) {
        int next = pi[ans.back() - 1];
        if (next == 0)
            break;
        ans.push_back(next);
    }
    reverse(ans.begin(), ans.end());

    for (int i : ans)
        cout << i << " ";

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
