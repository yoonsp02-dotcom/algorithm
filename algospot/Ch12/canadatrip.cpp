#include <bits/stdc++.h>

using namespace std;

int T, N;
long long K;
vector<int> L, M, G;

long long cntSigns(int distance);
bool decision(int distance);
int optimize();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> N >> K;
        L.resize(N);
        M.resize(N);
        G.resize(N);
        for (int i = 0; i < N; ++i)
            cin >> L[i] >> M[i] >> G[i];
        cout << optimize() << "\n";
    }

    return 0;
}

long long cntSigns(int distance) {
    long long ret = 0;
    for (int i = 0; i < N; ++i) {
        int start = L[i] - M[i];
        int end = min(L[i], distance);
        if (distance >= start) {
            ret += (end - start) / G[i] + 1;
        }
    }
    return ret;
}

bool decision(int distance) { return cntSigns(distance) >= K; }

int optimize() {
    int lo = 0, hi = 8030000;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (decision(mid))
            hi = mid;
        else
            lo = mid;
    }
    return hi;
}