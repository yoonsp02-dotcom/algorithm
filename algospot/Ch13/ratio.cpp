#include <bits/stdc++.h>

using namespace std;

const long long maxWin = 2000000000;
int T, N, M;
// 현재 승률(정수 부분) 계산 함수
long long winRate(long long games, long long win);
// 승률을 올리기 위해 필요한 최소 연승 수를 계산하는 함수
long long cntWin(long long games, long long win);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> N >> M;
        cout << cntWin(N, M) << "\n";
    }

    return 0;
}

long long winRate(long long games, long long win) { return 100 * win / games; }

long long cntWin(long long games, long long win) {
    // 현재 승률과 20억번 연승했을 때 승률이 같으면 승률 증가가 불가능
    if (winRate(games, win) == winRate(games + maxWin, win + maxWin))
        return -1;
    long long lo = 0, hi = maxWin;
    while (lo + 1 < hi) {
        long long mid = (lo + hi) / 2;
        if (winRate(games, win) == winRate(games + mid, win + mid))
            lo = mid;
        else
            hi = mid;
    }
    return hi;
}