#include <bits/stdc++.h>

using namespace std;

int primary, secondary;
long long cntProctor(int studentCnt);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    cin >> N;
    vector<int> studentsInRoom(N);
    for (int i = 0; i < N; ++i) {
        cin >> studentsInRoom[i];
    }
    cin >> primary >> secondary;
    long long res = 0;
    for (int i = 0; i < N; ++i) {
        res += cntProctor(studentsInRoom[i]);
    }
    cout << res << "\n";

    return 0;
}

long long  cntProctor(int students) {
    long long ret = 1;
    students -= primary;
    if (students <= 0)
        return ret;
    // plus ceil
    ret += (students - 1) / secondary + 1;
    return ret;
}