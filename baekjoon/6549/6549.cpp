#include <bits/stdc++.h>

using namespace std;
vector<int> h;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    return 0;
}
// [s, e)
int getMaxRec(int s, int e) {
    if (s == e) {
        return h[s];
    }
    int mid = (s + e) / 2;
    int ret = getMaxRec(s, mid);
    ret = max(ret, getMaxRec(mid, e));
    
}