#include <bits/stdc++.h>

using namespace std;

int C;

vector<vector<int>> adj;
vector<int> sccId;
vector<int> discovered;
stack<int> st;
int sccCounter, vertexCounter;

int scc(int here);
vector<int> tarjanSCC();
bool disjoint(const pair<int, int> &a, const pair<int, int> &b);
void makeGraph(const vector<pair<int, int>> &meetings);
vector<int> solve2SAT();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int teams;
        cin >> teams;
        vector<pair<int, int>> meetings;
        for (int i = 0; i < teams; ++i) {
            int s1, e1, s2, e2;
            cin >> s1 >> e1 >> s2 >> e2;
            meetings.push_back({s1, e1});
            meetings.push_back({s2, e2});
        }
        makeGraph(meetings);
        vector<int> ans = solve2SAT();
        if (ans.empty()) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << "POSSIBLE\n";
            for (int i = 0; i < ans.size(); ++i)
                if (ans[i])
                    cout << meetings[i].first << " " << meetings[i].second
                         << "\n";
        }
    }

    return 0;
}

int scc(int here) {
    int ret = discovered[here] = vertexCounter++;
    st.push(here);
    for (int i = 0; i < adj[here].size(); ++i) {
        int there = adj[here][i];
        if (discovered[there] == -1) {
            ret = min(ret, scc(there));
        } else if (sccId[there] == -1) {
            ret = min(ret, discovered[there]);
        }
    }

    if (ret == discovered[here]) {
        while (true) {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if (t == here)
                break;
        }
        ++sccCounter;
    }
    return ret;
}

vector<int> tarjanSCC() {
    sccId = discovered = vector<int>(adj.size(), -1);
    sccCounter = vertexCounter = 0;
    for (int i = 0; i < adj.size(); ++i)
        if (discovered[i] == -1)
            scc(i);
    return sccId;
}

bool disjoint(const pair<int, int> &a, const pair<int, int> &b) {
    return (a.second <= b.first) || (b.second <= a.first);
}

void makeGraph(const vector<pair<int, int>> &meetings) {
    int n = meetings.size();
    adj.clear();
    adj.resize(2 * n);
    for (int i = 0; i < n; i += 2) {
        int j = i + 1;
        adj[2 * i + 1].push_back(2 * j);
        adj[2 * j + 1].push_back(2 * i);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (!disjoint(meetings[i], meetings[j])) {
                adj[2 * i].push_back(2 * j + 1);
                adj[2 * j].push_back(2 * i + 1);
            }
        }
    }
}

vector<int> solve2SAT() {
    int n = adj.size() / 2;
    vector<int> label = tarjanSCC();
    for (int i = 0; i < n; ++i) {
        if (label[2 * i] == label[2 * i + 1])
            return vector<int>();
    }

    vector<int> value(n, -1);
    vector<pair<int, int>> order;
    for (int i = 0; i < 2 * n; ++i) {
        order.push_back({-label[i], i});
    }
    sort(order.begin(), order.end());

    for (int i = 0; i < 2 * n; ++i) {
        int vertex = order[i].second;
        int variable = vertex / 2;
        int isTrue = (vertex % 2 == 0);
        if (value[variable] != -1)
            continue;
        value[variable] = !isTrue;
    }
    return value;
}