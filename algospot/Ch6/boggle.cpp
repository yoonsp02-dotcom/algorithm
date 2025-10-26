#include <bits/stdc++.h>

using namespace std;

int C, N;
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
vector<string> board(5);

void divide(const string &word, string &f, string &b);
bool isInside(int y, int x);
bool check(int y, int x, int idx,
           string &w); //(y, x) == w[idx]일 때 w가 board에 있는지

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        for (int i = 0; i < 5; ++i)
            cin >> board[i];

        cin >> N;
        for (int i = 0; i < N; ++i) {
            string word;
            cin >> word;
            string f, b;
            divide(word, f, b);

            bool isChecked = false;
            for (int y = 0; y < 5; ++y) {
                for (int x = 0; x < 5; ++x) {
                    if (board[y][x] == word[word.size() / 2]) {
                        if (check(y, x, 0, f) && check(y, x, 0, b)) {
                            isChecked = true;
                            break;
                        }
                    }
                }
            }
            cout << word << (isChecked ? " YES\n" : " NO\n");
        }
    }

    return 0;
}

void divide(const string &word, string &f, string &b) {
    int s = word.size() / 2;
    f = word.substr(0, s + 1);
    b = word.substr(s);
    reverse(f.begin(), f.end());
}

bool isInside(int y, int x) { return (0 <= y && y < 5 && 0 <= x && x < 5); }
bool check(int y, int x, int idx, const string &w) {
    if (idx == w.size() - 1)
        return true;

    for (int i = 0; i < 8; ++i) {
        int ny = y + dy[i], nx = x + dx[i];
        if (!isInside(ny, nx))
            continue;

        if (board[ny][nx] == w[idx + 1])
            if (check(ny, nx, idx + 1, w))
                return true;
    }
    return false;
}

// solved by DP
// #include <bits/stdc++.h>

// using namespace std;

// int C, N;
// int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
// int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
// int cache[5][5][10];
// vector<string> board(5);

// bool isInside(int y, int x);
// int check(int y, int x, int idx, const string &w);

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);

//     cin >> C;
//     while (C--) {
//         for (int i = 0; i < 5; ++i)
//             cin >> board[i];

//         cin >> N;
//         for (int i = 0; i < N; ++i) {
//             string word;
//             cin >> word;
//             memset(cache, -1, sizeof(cache));
//             bool isChecked = false;
//             for (int y = 0; y < 5; ++y) {
//                 for (int x = 0; x < 5; ++x) {
//                     if (check(y, x, 0, word)) {
//                         isChecked = true;
//                         break;
//                     }
//                 }
//             }
//             cout << word << (isChecked ? " YES\n" : " NO\n");
//         }
//     }

//     return 0;
// }

// bool isInside(int y, int x) { return (0 <= y && y < 5 && 0 <= x && x < 5); }

// int check(int y, int x, int idx, const string &w) {
//     if (!isInside(y, x))
//         return 0;
//     if (idx == w.size())
//         return 1;
//     if (board[y][x] != w[idx])
//         return 0;

//     int &ret = cache[y][x][idx];
//     if (ret != -1)
//         return ret;

//     ret = 0;
//     for (int i = 0; i < 8; ++i) {
//         int ny = y + dy[i], nx = x + dx[i];
//         if (check(ny, nx, idx + 1, w))
//             return ret = 1;
//     }
//     return ret;
// }