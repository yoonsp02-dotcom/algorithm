#include <bits/stdc++.h>

using namespace std;

const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int N;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N;
    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N; ++j) 
            cin >> board[i][j];
        
    cout << game(board) << endl;

    return 0;
}
int& getNearestInDir(int i, int j, int dir) {
    
}
void move(vector<vector<int>>& board, int dir) {
    vector<int> blank(N, 0);
    if (dir == UP) {
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == 0) {
                    blank[j] = i;
                } else {
                    int &now = board[i][j];
                    int &under = getNearestInDir(i, j, dir);
                    
                }
            }
        }
    }
}
// 5번 이동 후 가장 큰 값 return
int game(vector<vector<int>>& board) {
 //11
}