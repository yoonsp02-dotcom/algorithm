#include <bits/stdc++.h>

using namespace std;

const long long MAX = 2 * 1000 * 1000 * 1000 + 1;
int C, N, K;
int cache[501];
int sequence[501];
int lisCnt[501];

int lis(int idx);
void sol(int idx, int skip, vector<int> &ans);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(cache, -1, sizeof(cache));
        memset(sequence, 0, sizeof(sequence));

        cin >> N >> K;
        for (int i = 1; i <= N; ++i)
            cin >> sequence[i];
        sequence[0] = -1;

        for (int i = 0; i <= N; ++i) {
            lisCnt[i] = 0;
        }

        for (int i = N; i >= 0; --i) {
            if (lis(i) == 1) {
                lisCnt[i] = 1;
                continue;
            }
            for (int j = i + 1; j <= N; ++j) {
                if (lis(i) == lis(j) + 1 && sequence[i] < sequence[j]) {
                    lisCnt[i] =
                        min<long long>(MAX, (long long)lisCnt[i] + lisCnt[j]);
                }
            }
        }

        vector<int> ans;

        cout << lis(0) - 1 << "\n";
        sol(0, K - 1, ans);
        for (int i = 0; i < ans.size(); ++i)
            cout << ans[i] << " ";
        cout << "\n";
    }

    return 0;
}

int lis(int idx) {
    int &ret = cache[idx];
    if (ret != -1)
        return ret;

    ret = 1;
    for (int next = idx + 1; next <= N; ++next) {
        if (sequence[next] > sequence[idx]) {
            ret = max(ret, 1 + lis(next));
        }
    }

    return ret;
}

void sol(int idx, int skip, vector<int> &ans) {
    stack<int> st;
    for (int next = idx + 1; next <= N; ++next) {
        if (sequence[idx] < sequence[next] && lis(next) == lis(idx) - 1)
            st.push(next);
    }

    while (!st.empty()) {
        if (skip < lisCnt[st.top()])
            break;
        skip -= lisCnt[st.top()];
        st.pop();
    }
    if (st.empty())
        return;

    ans.push_back(sequence[st.top()]);
    sol(st.top(), skip, ans);

    while (!st.empty())
        st.pop();
}