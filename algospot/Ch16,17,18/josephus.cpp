#include <bits/stdc++.h>

using namespace std;

int C, N, K;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N >> K;
        list<int> l;
        for (int i = 1; i <= N; ++i)
            l.push_back(i);

        list<int>::iterator it = l.begin();
        while (l.size() > 2) {
            it = l.erase(it);
            if (it == l.end())
                it = l.begin();
            for (int i = 0; i < K - 1; ++i) {
                ++it;
                if (it == l.end())
                    it = l.begin();
            }
        }

        cout << l.front() << " " << l.back() << "\n";
    }

    return 0;
}