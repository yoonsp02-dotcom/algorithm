#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int C;
    cin >> C;
    cin.ignore();
    for (int i = 0; i < C; ++i) {
        string name;
        getline(cin, name);
        int gCnt = count(name.begin(), name.end(), 'g') +
                    count (name.begin(), name.end(), 'G');
        int bCnt = count(name.begin(), name.end(), 'b') +
                   count(name.begin(), name.end(), 'B');
        if (gCnt > bCnt)
            cout << name << " is GOOD\n";
        else if (gCnt < bCnt)
            cout << name << " is A BADDY\n";
        else
            cout << name << " is NEUTRAL\n";
    }


    return 0;
}