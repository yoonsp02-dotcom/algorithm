#include <bits/stdc++.h>

using namespace std;

int C, N, M;
vector<double> location;

bool decision(const vector<double> &location, int cameras, double gap);
double optimize(const vector<double> &location, int cameras);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N >> M;
        location.resize(M);
        for (int i = 0; i < M; ++i) {
            cin >> location[i];
        }
        cout << fixed;
        cout.precision(2);
        cout << optimize(location, N) << "\n";
    }

    return 0;
}

bool decision(const vector<double> &location, int cameras, double gap) {
    double last = -1;
    int installed = 0;
    for (int i = 0; i < location.size(); ++i) {
        if (last <= location[i]) {
            ++installed;
            last = location[i] + gap;
        }
    }
    return installed >= cameras;
}

double optimize(const vector<double> &location, int cameras) {
    double lo = 0, hi = 241;
    for (int it = 0; it < 100; ++it) {
        double mid = (lo + hi) / 2;
        if (decision(location, cameras, mid))
            lo = mid;
        else
            hi = mid;
    }
    return lo;
}