#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
int C, N, S;
vector<int> num;
int cache[101][11];

int mean(int idx, int next);
int calSSE(int idx, int next, int mean);
int quantize(int idx, int s);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        memset(cache, -1, sizeof(cache));

        cin >> N >> S;
        num = vector<int>(N, 0);
        for (int i = 0; i < N; ++i)
            cin >> num[i];
        sort(num.begin(), num.end());

        cout << quantize(0, S) << "\n";
    }

    return 0;
}

// round mean of index of num[idx, next)
int mean(int idx, int next) {
    double sum = 0.0;
    for (int i = idx; i < next; ++i) {
        sum += num[i];
    }
    return round(sum / (next - idx));
}

// calculate SSE of num[idx, next) when mean == m
int calSSE(int idx, int next, int m) {
    int ret = 0;
    for (int i = idx; i < next; ++i) {
        ret += (num[i] - m) * (num[i] - m);
    }

    return ret;
}

int quantize(int idx, int s) {
    if (idx == N)
        return 0;
    if (s == 0)
        return INF;

    int &ret = cache[idx][s];
    if (ret != -1)
        return ret;

    ret = INF;
    for (int next = idx + 1; next <= N; ++next) {
        int m = mean(idx, next);
        int c = calSSE(idx, next, m);
        ret = min(ret, quantize(next, s - 1) + c);
    }

    return ret;
}