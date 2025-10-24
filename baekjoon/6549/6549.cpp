#include <bits/stdc++.h>

using namespace std;
vector<int> h;
int n;
int getMaxRec(int, int);
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while(true) {
        cin >> n;
        if (n == 0)
            break;
        h = vector<int>(n);
        for (int i = 0; i < n; ++i)
            cin >> h[i];
        cout << getMaxRec(0, n) << "\n";
    }

    return 0;
}
// [s, e)
int getMaxRec(int s, int e) {
    // cout << "start " << s << " " << e << endl;
    if (s + 1 == e) {
        return h[s];
    }
    int mid = (s + e) / 2;
    int ret = getMaxRec(s, mid);
    ret = max(ret, getMaxRec(mid, e));
    int left = mid, right = mid + 1;
    int height = min(h[left], h[right]);
    while (left >= 0 && right < n) {
        height = min(height, min(h[left], h[right]));
        ret = max(ret, height * (right - left + 1));
        if (left == 0 && right == n - 1)
            break;
        else if (left == 0)
            right++;
        else if (right == n - 1)
            left--;
        else if (h[left - 1] < h[right + 1])
            right++;
        else
            left--;
    }
    // cout << "finish " << s << " " << e << endl;
    return ret;
}