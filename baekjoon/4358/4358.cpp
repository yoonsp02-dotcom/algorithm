#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    map<string, int> m;
    string key;
    int cnt = 0;
    while (getline(cin, key)) {
        m[key]++;
        cnt++;
    }

    cout << fixed;
    cout.precision(4);
    for (auto& it : m) {
        cout << it.first << " " << it.second * 100.0 / cnt << "\n";
    }
    
    return 0;
}