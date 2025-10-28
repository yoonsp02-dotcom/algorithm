#include <bits/stdc++.h>

using namespace std;

int T, n, k;
int c[1000], r[1000];

bool decision(double cr);
double optimize();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 0; i < n; ++i)
            cin >> r[i] >> c[i];
        cout << fixed;
        cout.precision(10);
        cout << optimize() << "\n";
    }

    return 0;
}

bool decision(double cr) {
    vector<double> v;
    for (int i = 0; i < n; ++i)
        v.push_back(cr * c[i] - r[i]);
    sort(v.begin(), v.end());
    double sum = 0;
    for (int i = n - k; i < n; ++i)
        sum += v[i];
    return sum >= 0;
}

double optimize() {
    double lo = -1e-9, hi = 1;
    for (int it = 0; it < 100; ++it) {
        double mid = (lo + hi) / 2;
        if (decision(mid))
            hi = mid;
        else
            lo = mid;
    }
    return hi;
}