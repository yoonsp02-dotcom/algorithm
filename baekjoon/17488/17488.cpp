#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int N, M;
    cin >> N >> M;
    vector<int> classSize(M+1);
    vector<vector<int>> tryAttend(M+1);
    vector<vector<int>> successAttend(N);

    for (int i = 1; i < M+1; ++i) {
        cin >> classSize[i];
    }

    for (int iter = 0; iter < 2; ++iter) {
        for (int student = 0; student < N; ++student) {
            while (true) {
                int sub;
                cin >> sub;
                if (sub == -1) break;
                tryAttend[sub].push_back(student);
            }
        }

        for (int sub = 1; sub < M+1; ++sub) {
            if (tryAttend[sub].size() <= classSize[sub]) {
                for (int stu : tryAttend[sub])
                    successAttend[stu].push_back(sub);
                classSize[sub] -= tryAttend[sub].size();
                tryAttend[sub].clear();
            }
        }
    }

    for (int stu = 0; stu < N; ++stu) {
        if (successAttend[stu].size() == 0)
            cout << "망했어요\n";
        else {
            sort(successAttend[stu].begin(), successAttend[stu].end());
            for (int sub : successAttend[stu])
                cout << sub << " ";
            cout << "\n";
        }
    }
    return 0;
}