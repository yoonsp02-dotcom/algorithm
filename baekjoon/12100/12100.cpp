#include <bits/stdc++.h>

using namespace std;

const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {-1, 1, 0, 0};
int N;

struct State {
    vector<vector<int>> board;
    int level;
    State(vector<vector<int>> _board, int _level) : board(_board), level(_level) {} 
};

vector<int> compressLine(const vector<int> &line);
void moveLeft(vector<vector<int>>& board);
vector<vector<int>> rotateBoard(const vector<vector<int>> &board);
void move(vector<vector<int>> &board, int dir);
int getMax(const vector<vector<int>> &board);
int game(vector<vector<int>> &board);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N;
    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
        }
    }

    cout << game(board) << endl;

    return 0;
}
vector<int> compressLine(const vector<int> &line) {
    vector<int> nums;
    for (int x : line) {
        if (x != 0)
            nums.push_back(x);
    }
    vector<int> merged;
    for (int i = 0; i < nums.size(); ++i) {
        if (i + 1 < nums.size() && nums[i] == nums[i + 1]) {
            merged.push_back(nums[i] * 2);
            i++;
        } else {
            merged.push_back(nums[i]);
        }
    }

    while (merged.size() < N)
        merged.push_back(0);
    return merged;
}
void moveLeft(vector<vector<int>>& board) {
    for (int y = 0; y < N; ++y) {
        board[y] = compressLine(board[y]);
    }
}
vector<vector<int>> rotateBoard(const vector<vector<int>> &board) {
    vector<vector<int>> ret(N, vector<int>(N));
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            ret[x][N - 1 - y] = board[y][x];
        }
    }
    return ret;
}
void move(vector<vector<int>> &board, int dir) {
    if (dir == LEFT) {
        moveLeft(board);
    } else if (dir == RIGHT) {
        board = rotateBoard(board);
        board = rotateBoard(board);
        moveLeft(board);
        board = rotateBoard(board);
        board = rotateBoard(board);
    } else if (dir == UP) {
        board = rotateBoard(board);
        board = rotateBoard(board);
        board = rotateBoard(board);
        moveLeft(board);
        board = rotateBoard(board);
    } else if (dir == DOWN) {
        board = rotateBoard(board);
        moveLeft(board);
        board = rotateBoard(board);
        board = rotateBoard(board);
        board = rotateBoard(board);
    }
}
int getMax(const vector<vector<int>> &board) {
    int ret = 0;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            ret = max(ret, board[i][j]);
        }
    }
    return ret;
}
int game(vector<vector<int>> &board) {
    queue<State> q;
    q.push(State(board, 0));
    int ret = 0;
    while (!q.empty()) {
        State here = q.front();
        q.pop();

        if (here.level == 5) {
            ret = max(ret, getMax(here.board));
            continue;
        }
        for (int dir = UP; dir <= LEFT; ++dir) {
            vector<vector<int>> board = here.board;
            move(board, dir);
            State there(board, here.level + 1);
            q.push(there);
        }
    }
    return ret;
}