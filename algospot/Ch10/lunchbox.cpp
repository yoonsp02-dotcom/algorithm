#include <bits/stdc++.h>

using namespace std;

int C, N;
vector<int> m, eat;
vector<pair<int, int>> order;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N;
        m.clear();
        eat.clear();
        order.clear();
        m = vector<int>(N);
        eat = vector<int>(N);
        for (int i = 0; i < N; ++i)
            cin >> m[i];
        for (int i = 0; i < N; ++i)
            cin >> eat[i];
        for (int i = 0; i < N; ++i)
            order.push_back(make_pair(eat[i], m[i]));

        sort(order.begin(), order.end(), greater<pair<int, int>>());

        int microTime = 0, lunchTime = 0;
        for (int i = 0; i < N; ++i) {
            microTime += order[i].second;
            lunchTime = max(lunchTime, microTime + order[i].first);
        }
        cout << lunchTime << "\n";
    }

    return 0;
}