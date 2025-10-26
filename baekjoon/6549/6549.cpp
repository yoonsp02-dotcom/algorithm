#include <bits/stdc++.h>

using namespace std;
vector<long long> h;
int n;
long long getMaxRec(int, int);
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    while(true) {
        cin >> n;
        if (n == 0)
            break;
        h = vector<long long>(n);
        for (int i = 0; i < n; ++i)
            cin >> h[i];
        cout << getMaxRec(0, n - 1) << "\n";
    }

    return 0;
}
// [s, e]
long long getMaxRec(int s, int e) {
    // cout << "start " << s << " " << e << endl;
    if (s == e) {
        // cout << "finish " << s << " " << e << endl;
        return h[s];
    }
    int mid = (s + e) / 2;
    long long ret = getMaxRec(s, mid);
    ret = max(ret, getMaxRec(mid + 1, e));
    int left = mid, right = mid + 1;
    long long height = min(h[left], h[right]);
    while (s <= left && right <= e) {
        height = min(height, min(h[left], h[right]));
        ret = max(ret, height * (right - left + 1));
        if (left == s)
            right++;
        else if (right == e)
            left--;
        else if (h[left - 1] < h[right + 1])
            right++;
        else
            left--;
    }
    // cout << "finish " << s << " " << e << endl;
    return ret;
}