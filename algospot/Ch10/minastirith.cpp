#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0);
const int INF = 987654321;
int C, N;
double y[100], x[100], r[100];
pair<double, double> ranges[100];

void convertToRange();
int solveLinear(double begin, double end);
int solveCircular();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> y[i] >> x[i] >> r[i];
        }
        convertToRange();
        int ans = solveCircular();
        if (ans == INF)
            cout << "IMPOSSIBLE" << "\n";
        else
            cout << ans << "\n";
    }

    return 0;
}

void convertToRange() {
    for (int i = 0; i < N; ++i) {
        double c = atan2(y[i], x[i]);
        c = fmod(c + 2 * PI, 2 * PI);
        double range = 2 * asin(r[i] / 2 / 8.0);
        ranges[i] = make_pair(c - range, c + range);
    }
    sort(ranges, ranges + N);
}

int solveLinear(double begin, double end) {
    int used = 0, idx = 0;
    while (begin < end) {
        double maxCover = -1;
        while (idx < N && ranges[idx].first <= begin) {
            maxCover = max(maxCover, ranges[idx].second);
            idx++;
        }
        if (maxCover <= begin)
            return INF;

        begin = maxCover;
        ++used;
    }
    return used;
}

int solveCircular() {
    int ret = INF;
    sort(ranges, ranges + N);
    for (int i = 0; i < N; ++i) {
        if (ranges[i].first <= 0 || ranges[i].second >= 2 * PI) {
            double begin = fmod(ranges[i].second, 2 * PI);
            double end = fmod(ranges[i].first + 2 * PI, 2 * PI);
            ret = min(ret, 1 + solveLinear(begin, end));
        }
    }
    return ret;
}