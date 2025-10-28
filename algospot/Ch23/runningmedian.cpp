#include <bits/stdc++.h>

using namespace std;

const int MOD = 20090711;
int C, a, b;

int makeInput(int seed) { return (seed * (long long)a + b) % MOD; }

int runningMedian(int seed);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int n;
        cin >> n >> a >> b;

        cout << runningMedian(n) << "\n";
    }

    return 0;
}

int runningMedian(int n) {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    int seed = 1983;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (maxHeap.empty() || seed <= maxHeap.top()) {
            maxHeap.push(seed);
        } else {
            minHeap.push(seed);
        }

        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        ans = (ans + maxHeap.top()) % MOD;
        seed = makeInput(seed);
    }
    return ans;
}