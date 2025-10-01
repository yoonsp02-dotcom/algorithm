#include <bits/stdc++.h>

using namespace std;

int N;
int cache[16], t[16], p[16];

int getMaxMoney(int today);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    memset(cache, -1, sizeof(cache));
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> t[i] >> p[i];
    }

    cout << getMaxMoney(1) << "\n";

    return 0;
}

int getMaxMoney(int today) {
    if (today > N) 
        return 0;
    
    int &ret = cache[today];
    if (ret != -1) {
        return ret;
    }
    // 기간 안에 처리 가능
    // today 상담을 고른 경우
    if (today + t[today] - 1 <= N) {
        ret = max(ret, p[today] + getMaxMoney(today + t[today]));
    }
    // today 상담을 고르지 않은 경우
    ret = max(ret, getMaxMoney(today + 1));

    return ret;
}