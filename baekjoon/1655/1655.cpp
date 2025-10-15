#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    priority_queue<int> frontHalf;
    priority_queue<int, vector<int>, greater<int>> backHalf;
    int N;
    cin >> N;
    // frontHalf.size() == backHalf.size() or + 1
    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;
        if (frontHalf.size() == backHalf.size()) {
            if (!backHalf.empty() && num > backHalf.top()) {
                frontHalf.push(backHalf.top());
                backHalf.pop();
                backHalf.push(num);
            } else
                frontHalf.push(num);
        }
        else { 
            if (!frontHalf.empty() && num < frontHalf.top()) {
                backHalf.push(frontHalf.top());
                frontHalf.pop();
                frontHalf.push(num);
            }
            else
                backHalf.push(num);
        }
        
        cout << frontHalf.top() << "\n";
    }

    return 0;
}
