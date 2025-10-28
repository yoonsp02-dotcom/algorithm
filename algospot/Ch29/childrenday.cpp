#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> digits;

string toyCount() {
    int mod = N;
    vector<bool> visited(mod, false);
    queue<pair<string, int>> q;

    for (int d : digits) {
        if (d == 0)
            continue;
        int remain = d % mod;
        string s = to_string(d);

        if (remain == M)
            if (s.size() > to_string(N).size() || stoi(s) >= N)
                return s;

        q.push({s, remain});
        visited[remain] = true;
    }

    while (!q.empty()) {
        pair<string, int> here = q.front();
        string cur = here.first;
        int rem = here.second;
        q.pop();

        for (int d : digits) {
            string next = cur + char('0' + d);
            int next_rem = (rem * 10 + d) % mod;

            if (next_rem == M)
                if (next.size() > to_string(N).size() || stoi(next) >= N)
                    return next;
            if (visited[next_rem])
                continue;

            visited[next_rem] = true;
            q.push({next, next_rem});
        }
    }
    return "IMPOSSIBLE";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s >> N >> M;
        digits.clear();
        for (char c : s)
            digits.push_back(c - '0');
        sort(digits.begin(), digits.end());

        cout << toyCount() << "\n";
    }
    return 0;
}
