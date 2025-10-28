#include <bits/stdc++.h>

using namespace std;

int T, n, m, best;
vector<string> friends;
map<string, int> friendIdx;
vector<vector<int>>
    foodCanEat; // foodCanEat[i] = i번 음식을 먹을 수 있는 친구들의 idx
vector<vector<int>>
    personCanEat; // personCanEat[i] = i번 친구가 먹을 수 있는 음식들

void search(vector<int> &covered, int chosen);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> n >> m;
        friends.resize(n);
        friendIdx.clear();
        foodCanEat.assign(m, {});
        personCanEat.assign(n, {});

        for (int i = 0; i < n; ++i) {
            cin >> friends[i];
            friendIdx[friends[i]] = i;
        }

        for (int i = 0; i < m; ++i) {
            int cnt;
            cin >> cnt;
            while (cnt--) {
                string name;
                cin >> name;
                int idx = friendIdx[name];
                foodCanEat[i].push_back(idx);
                personCanEat[idx].push_back(i);
            }
        }

        best = m;
        vector<int> covered(n, 0);
        search(covered, 0);
        cout << best << "\n";
    }

    return 0;
}

void search(vector<int> &covered, int chosen) {
    if (best <= chosen)
        return;

    bool allCovered = true;
    for (int c : covered)
        if (!c) {
            allCovered = false;
            break;
        }
    if (allCovered) {
        best = chosen;
        return;
    }

    // 먹을 음식이 없는 사람들 중 먹을 수 있는 음식의 수가 가장 적은 사람 선택
    int foodCnt = m, target = -1;
    for (int i = 0; i < personCanEat.size(); ++i) {
        if (covered[i])
            continue;
        int cnt = personCanEat[i].size();
        if (cnt < foodCnt) {
            foodCnt = cnt;
            target = i;
        }
    }

    // 선택한 사람이 먹을 수 있는 음식들을 먹을 수 있는 사람의 수가 많은 순으로
    // 시도
    vector<pair<int, int>> candidates;
    for (int f : personCanEat[target]) {
        int coverCount = 0;
        for (int p : foodCanEat[f]) {
            if (!covered[p])
                coverCount++;
        }
        candidates.push_back({-coverCount, f});
    }
    sort(candidates.begin(), candidates.end());

    for (auto c : candidates) {
        int food = c.second;
        for (int p : foodCanEat[food])
            covered[p]++;

        search(covered, chosen + 1);

        for (int p : foodCanEat[food])
            covered[p]--;
    }
}