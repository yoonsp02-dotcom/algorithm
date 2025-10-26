#include <iostream>
#include <vector>

using namespace std;

int c, n, m;
int match[10][10];
int matched(vector<bool> &taken);

int main() {
    cin >> c;
    while (c--) {
        vector<bool> taken(10, false);
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                match[i][j] = 0;

        cin >> n >> m;
        for (int i = 0; i < m; ++i) {
            int f1, f2;
            cin >> f1 >> f2;
            match[f1][f2] = match[f2][f1] = 1;
        }

        cout << matched(taken) << '\n';
    }

    return 0;
}

// state가 taken일때 짝지을 수 있는 방법의 수를 return
int matched(vector<bool> &taken) {
    int noFriend = -1;
    for (int i = 0; i < n; ++i) {
        if (!taken[i]) {
            noFriend = i;
            break;
        }
    }
    if (noFriend == -1)
        return 1;

    int ret = 0;

    for (int canPair = noFriend + 1; canPair < n; ++canPair) {
        if (match[noFriend][canPair] && !taken[canPair]) {
            taken[canPair] = taken[noFriend] = true;
            ret += matched(taken);
            taken[canPair] = taken[noFriend] = false;
        }
    }

    return ret;
}