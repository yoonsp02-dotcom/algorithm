#include <bits/stdc++.h>

using namespace std;

int C, N;
vector<pair<double, double>> stations;

double getDistance(pair<double, double> &s1, pair<double, double> &s2);
bool decision(double d);
double optimize();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N;
        stations.resize(N);
        for (int i = 0; i < N; ++i) {
            double y, x;
            cin >> y >> x;
            stations[i] = {y, x};
        }
        cout << fixed;
        cout.precision(2);
        cout << optimize() << "\n";
    }

    return 0;
}

double getDistance(int s1, int s2) {
    return sqrt(pow(stations[s1].first - stations[s2].first, 2) +
                pow(stations[s1].second - stations[s2].second, 2));
}

bool decision(double d) {
    vector<bool> visited(stations.size(), false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        for (int there = 0; there < stations.size(); ++there) {
            if (visited[there])
                continue;
            if (getDistance(here, there) <= d) {
                q.push(there);
                visited[there] = true;
            }
        }
    }

    for (int i = 0; i < visited.size(); ++i) {
        if (visited[i] == false)
            return false;
    }
    return true;
}

double optimize() {
    double lo = 1, hi = 1500;
    for (int it = 0; it < 100; ++it) {
        double mid = (lo + hi) / 2;
        if (decision(mid))
            hi = mid;
        else
            lo = mid;
    }
    return lo;
}