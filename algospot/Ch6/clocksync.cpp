#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
int c;
int clockState[16];
vector<int> sw[10];
bool check(int clockState[16]) {
    bool ok = true;
    for (int i = 0; i < 16; ++i) {
        if (clockState[i] != 0) {
            ok = false;
            break;
        }
    }
    return ok;
}
int pushCount(int clockState[16], int swNum);

int main() {
    sw[0] = vector<int>({0, 1, 2});
    sw[1] = vector<int>({3, 7, 9, 11});
    sw[2] = vector<int>({4, 10, 14, 15});
    sw[3] = vector<int>({0, 4, 5, 6, 7});
    sw[4] = vector<int>({6, 7, 8, 10, 12});
    sw[5] = vector<int>({0, 2, 14, 15});
    sw[6] = vector<int>({3, 14, 15});
    sw[7] = vector<int>({4, 5, 7, 14, 15});
    sw[8] = vector<int>({1, 2, 3, 4, 5});
    sw[9] = vector<int>({3, 4, 5, 9, 13});

    cin >> c;
    while (c--) {
        for (int i = 0; i < 16; ++i) {
            cin >> clockState[i];
            clockState[i] = clockState[i] / 3 % 4;
        }
        int ans = pushCount(clockState, 0);
        if (ans == INF)
            ans = -1;
        cout << ans << "\n";
    }

    return 0;
}

int pushCount(int clockState[16], int swNum) {
    if (check(clockState))
        return 0;
    if (swNum == 10)
        return INF;
    int ret = INF;
    for (int push = 0; push < 4; ++push) {
        for (int i = 0; i < sw[swNum].size(); ++i) {
            int clockNum = sw[swNum][i];
            clockState[clockNum] = (clockState[clockNum] + push) % 4;
        }
        ret = min(ret, push + pushCount(clockState, swNum + 1));
        for (int i = 0; i < sw[swNum].size(); ++i) {
            int clockNum = sw[swNum][i];
            clockState[clockNum] = (clockState[clockNum] + 4 - push) % 4;
        }
    }
    return ret;
}