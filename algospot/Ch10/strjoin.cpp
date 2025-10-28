#include <bits/stdc++.h>

using namespace std;

int C, N;

int strJoin(priority_queue<int> &len);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N;
        priority_queue<int> len;
        for (int i = 0; i < N; ++i) {
            int tmp;
            cin >> tmp;
            len.push(-tmp);
        }
        cout << strJoin(len) << "\n";
    }

    return 0;
}

int strJoin(priority_queue<int> &len) {
    int cost = 0;
    while (len.size() > 1) {
        int newStr = len.top();
        len.pop();
        newStr += len.top();
        len.pop();
        cost += newStr;
        len.push(newStr);
    }
    return -cost;
}