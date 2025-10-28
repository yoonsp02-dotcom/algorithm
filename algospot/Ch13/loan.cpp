#include <bits/stdc++.h>

using namespace std;

int T, M;
double N, P;

bool balance(double C);
double loan();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> N >> M >> P;
        cout << fixed;
        cout.precision(10);
        cout << loan() << "\n";
    }

    return 0;
}
// 상환액 C로 M개월 안에 대출을 다 갚을 수 있는지를 판단하는 함수
bool balance(double C) {
    double ret = N;
    for (int i = 0; i < M; ++i) {
        ret *= 1 + P / 12 / 100;
        ret -= C;
        // 잔금이 0 이하로 떨어지면 상환 완료
        if (ret <= 0)
            return true;
    }
    // M개월이 지나도 잔금이 남았다면 상환 X => false
    return false;
}
// 이분 탐색으로 최소 월 상환액 C를 구하는 함수
double loan() {
    // lo: 0원, hi: M개월 후 상환할 수 있는 값
    double lo = 0, hi = N * (1 + P / 12 / 100);
    for (int it = 0; it < 100; ++it) {
        double mid = (lo + hi) / 2;
        if (balance(mid))
            hi = mid;
        else
            lo = mid;
    }
    return hi;
}