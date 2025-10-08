#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
int N;
int nums[11];
int operators[4];

int calc(vector<int> masks);
int getMax(vector<int> masks);
int getMin(vector<int> masks);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> nums[i];
    for (int i = 0; i < 4; ++i)
        cin >> operators[i];

    vector<int> masks;
    for (int i = 0; i < 4; ++i) {
        for (int iter = 0; iter < operators[i]; ++iter) {
            masks.push_back(i);
        }
    }

    cout << getMax(masks) << "\n";
    cout << getMin(masks) << "\n";

    return 0;
}
int calc(vector<int> masks) {
    int ret = nums[0];
    for (int i = 0; i < N - 1; ++i) {
        if (masks[i] == 0) {
            ret += nums[i + 1];
        } else if (masks[i] == 1) {
            ret -= nums[i + 1];
        } else if (masks[i] == 2) {
            ret *= nums[i + 1];
        } else if (masks[i] == 3) {
            ret /= nums[i + 1];
        }
    }
    return ret;
}
int getMax(vector<int> masks) {
    int ret = -INF;
    do {
        ret = max(ret, calc(masks));
    } while (next_permutation(masks.begin(), masks.end()));
    return ret;
}
int getMin(vector<int> masks) {
    int ret = INF;
    do {
        ret = min(ret, calc(masks));
    } while (next_permutation(masks.begin(), masks.end()));
    return ret;
}