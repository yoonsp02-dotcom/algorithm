#include <bits/stdc++.h>

using namespace std;

int C;
vector<int> convert(const vector<int> &input);
void bfs(int n);
void preCalc();
int solve(const vector<int> &input);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    preCalc();
    while (C--) {
        int n;
        cin >> n;
        vector<int> input(n);
        for (int i = 0; i < n; ++i)
            cin >> input[i];
        cout << solve(input) << "\n";
    }

    return 0;
}

vector<int> convert(const vector<int> &input) {
    int n = input.size();
    vector<int> ret(n);
    for (int i = 0; i < n; ++i) {
        int smaller = 0;
        for (int j = 0; j < n; ++j) {
            if (input[j] < input[i])
                smaller++;
        }
        ret[i] = smaller;
    }
    return ret;
}

map<vector<int>, int> m;
void bfs(int n) {
    queue<vector<int>> q;
    vector<int> root(n);
    for (int i = 0; i < n; ++i)
        root[i] = i;

    m[root] = 0;
    q.push(root);
    while (!q.empty()) {
        vector<int> here = q.front();
        q.pop();
        int c = m[here];
        for (int s = 0; s < n; ++s) {
            for (int e = s + 2; e <= n; ++e) {
                reverse(here.begin() + s, here.begin() + e);
                if (m.find(here) == m.end()) {
                    m[here] = c + 1;
                    q.push(here);
                }
                reverse(here.begin() + s, here.begin() + e);
            }
        }
    }
}

void preCalc() {
    m.clear();
    for (int i = 1; i <= 8; ++i) {
        bfs(i);
    }
}

int solve(const vector<int> &input) {
    vector<int> a = convert(input);
    return m[a];
}