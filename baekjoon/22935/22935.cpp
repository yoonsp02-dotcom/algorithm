#include <bits/stdc++.h>

using namespace std;

string binaryStrawberry(int num);

    int
    main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int num;
        cin >> num;
        num %= 28;
        if (num == 0) num = 2;
        if (num > 15) {
            num = 30 - num;
        }
        cout << binaryStrawberry(num) << "\n";
    }


    return 0;
}

string binaryStrawberry(int num) {
    string ret = "";
    for (int i = 3; i >= 0; --i) {
        if (num & (1<<i))
            ret += "딸기";
        else
            ret += "V";
    }
    return ret;
}