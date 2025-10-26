#include <cstring>
#include <iostream>

using namespace std;

const double INF = 987654321.0;
int cost[1001];
int psum[1001];

int c, n, l;

int main() {
    memset(cost, 0, 1001 * sizeof(int));
    memset(psum, 0, 1001 * sizeof(int));
    cost[0] = psum[0] = 0;
    cin >> c;
    while (c--) {
        cin >> n >> l;
        for (int i = 1; i <= n; ++i) {
            cin >> cost[i];
            psum[i] = psum[i - 1] + cost[i];
        }

        double avg = INF;
        for (int i = 0; i <= n - l; ++i) {
            for (int days = l; i + days <= n; ++days) {
                avg = min(avg, double(psum[i + days] - psum[i]) / days);
            }
        }
        cout << fixed;
        cout.precision(11);
        cout << avg << '\n';
    }

    return 0;
}