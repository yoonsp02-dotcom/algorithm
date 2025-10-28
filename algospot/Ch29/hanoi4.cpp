#include <bits/stdc++.h>

using namespace std;

int C;

int getRod(int state, int disk) { return (state >> (2 * disk)) & 3; }
int setDisk(int state, int rod, int disk) {
    return (state & ~(3 << (2 * disk))) | (rod << (2 * disk));
}

int cost[1 << (2 * 12)];
int sgn(int x) {
    if (!x)
        return 0;
    return (x > 0) ? 1 : -1;
}
int incr(int x) { return (x > 0) ? x + 1 : x - 1; }

int bidir(int start, int end, int diskCnt) {
    if (start == end)
        return 0;
    memset(cost, 0, sizeof(cost));
    queue<int> q;
    cost[start] = 1;
    cost[end] = -1;
    q.push(start);
    q.push(end);
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        int top[4] = {-1, -1, -1, -1};
        for (int i = diskCnt - 1; i >= 0; --i) {
            top[getRod(here, i)] = i;
        }
        for (int from = 0; from < 4; ++from) {
            if (top[from] == -1)
                continue;
            for (int to = 0; to < 4; ++to) {
                if (from == to)
                    continue;
                if (top[to] == -1 || top[from] < top[to]) {
                    int next = setDisk(here, to, top[from]);
                    if (cost[next] == 0) {
                        cost[next] = incr(cost[here]);
                        q.push(next);
                    } else if (sgn(cost[here]) != sgn(cost[next])) {
                        return abs(cost[here]) + abs(cost[next]) - 1;
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int diskCnt;
        cin >> diskCnt;
        int start = 0, end = 0;
        for (int rod = 0; rod < 4; ++rod) {
            int n;
            cin >> n;
            while (n--) {
                int disk;
                cin >> disk;
                start = setDisk(start, rod, disk - 1);
            }
        }
        for (int i = 0; i < diskCnt; ++i) {
            end = setDisk(end, 3, i);
        }

        cout << bidir(start, end, diskCnt) << "\n";
    }

    return 0;
}
// // 시간초과 내 코드
// #include <bits/stdc++.h>

// using namespace std;

// // const int MAX_DISKS = 12;

// int getTop(const long long &state, int rod) {
//     for (int i = 1; i <= 12; ++i) {
//         if (state & ((long long)1 << (13 * rod + i))) {
//             return i;
//         }
//     }
//     return 0;
// }
// void popDisk(long long &state, int rod, int disk) {
//     state &= ~((long long)1 << (13 * rod + disk));
// }
// void pushDisk(long long &state, int rod, int disk) {
//     state |= (long long)1 << (13 * rod + disk);
// }
// bool canMoveDisk(long long &state, int fromRod, int toRod) {
//     int fromTop = getTop(state, fromRod);
//     int toTop = getTop(state, toRod);
//     if (fromTop == 0)
//         return false;
//     if (toTop != 0 && fromTop > toTop)
//         return false;
//     return true;
// }
// long long moveDisk(const long long &state, int fromRod, int toRod) {
//     long long next = state;
//     int disk = getTop(state, fromRod);
//     popDisk(next, fromRod, disk);
//     pushDisk(next, toRod, disk);
//     return next;
// }

// int sgn(int x) {
//     if (!x)
//         return 0;
//     return (x > 0) ? 1 : -1;
// }
// int incr(int x) {
//     if (x < 0)
//         return x - 1;
//     return x + 1;
// }

// int bidir(long long start, long long end) {
//     unordered_map<long long, int> m;
//     if (start == end)
//         return 0;
//     queue<long long> q;
//     m[start] = 1;
//     m[end] = -1;
//     q.push(start);
//     q.push(end);

//     while (!q.empty()) {
//         long long here = q.front();
//         q.pop();
//         for (int fromRod = 0; fromRod < 4; ++fromRod) {
//             int cost = m[here];
//             for (int toRod = 0; toRod < 4; ++toRod) {
//                 if (fromRod == toRod)
//                     continue;
//                 if (!canMoveDisk(here, fromRod, toRod))
//                     continue;
//                 long long next = moveDisk(here, fromRod, toRod);
//                 unordered_map<long long, int>::iterator it = m.find(next);
//                 if (it == m.end()) {
//                     m[next] = incr(cost);
//                     q.push(next);
//                 } else if (sgn(it->second) != sgn(cost)) {
//                     return abs(it->second) + abs(cost) - 1;
//                 }
//             }
//         }
//     }
//     return -1;
// }

// int C;

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);

//     cin >> C;
//     while (C--) {
//         int n;
//         cin >> n;
//         long long start = 0, end = 0;
//         // make start
//         for (int rod = 0; rod < 4; ++rod) {
//             int cnt;
//             cin >> cnt;
//             while (cnt--) {
//                 int disk;
//                 cin >> disk;
//                 pushDisk(start, rod, disk);
//             }
//         }

//         // make end
//         for (int disk = n; disk > 0; --disk)
//             pushDisk(end, 3, disk);

//         cout << bidir(start, end) << "\n";
//     }

//     return 0;
// }