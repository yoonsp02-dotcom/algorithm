#include <bits/stdc++.h>

using namespace std;

struct Gear {
    int left, right;
    vector<int> state;
    Gear(vector<int> _state) : left(6), right(2), state(_state) {}
    void turnCW() {
        left = (left + 7) % 8;
        right = (right + 7) % 8;
    }
    void turnCCW() {
        left = (left + 1) % 8;
        right = (right + 1) % 8;
    }
    int getLeft() { return state[left]; }
    int getRight() { return state[right]; }
    int getTop() { return state[(left + 2) % 8]; }
};
Gear *gears[4];

int getScore();
void turnGear(int GearNum, int dir);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    for (int i = 0; i < 4; ++i) {
        string s;
        cin >> s;
        vector<int> state;
        for (int j = 0; j < s.size(); ++j) {
            state.push_back(s[j] - '0');
        }
        gears[i] = new Gear(state);
    }

    int K;
    cin >> K;
    while (K--) {
        int gearNum, dir;
        cin >> gearNum >> dir;
        turnGear(gearNum - 1, dir);
    }

    cout << getScore() << "\n";

    return 0;
}

int getScore() {
    int score[4] = {1, 2, 4, 8};
    int res = 0;
    for (int i = 0; i < 4; ++i) {
        if (gears[i]->getTop()) {
            res += score[i];
        }
    }
    return res;
}
void turnGear(int gearNum, int dir) {
    queue<pair<int, int>> q;
    vector<bool> isTurned(4, false);
    q.push({gearNum, dir});
    isTurned[gearNum] = true;
    while (!q.empty()) {
        int nowGear = q.front().first;
        int nowDir = q.front().second;
        q.pop();

        if (nowGear > 0 && !isTurned[nowGear - 1]) {
            int leftGear = nowGear - 1;
            if (gears[leftGear]->getRight() != gears[nowGear]->getLeft()) {
                q.push({leftGear, -nowDir});
                isTurned[leftGear] = true;
            }
        }
        if (nowGear < 3 && !isTurned[nowGear + 1]) {
            int rightGear = nowGear + 1;
            if (gears[rightGear]->getLeft() != gears[nowGear]->getRight()) {
                q.push({rightGear, -nowDir});
                isTurned[rightGear] = true;
            }
        }

        if (nowDir == 1)
            gears[nowGear]->turnCW();
        else
            gears[nowGear]->turnCCW();
    }
}