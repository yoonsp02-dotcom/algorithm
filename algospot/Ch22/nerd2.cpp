#include <bits/stdc++.h>

using namespace std;

int C, N;
vector<int> p, q;

int nerd2();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> N;
        p = vector<int>(N);
        q = vector<int>(N);
        for (int i = 0; i < N; ++i)
            cin >> p[i] >> q[i];

        cout << nerd2() << "\n";
    }

    return 0;
}

int nerd2() {
    map<int, int> m;
    m[p[0]] = q[0];
    int ret = 1;
    for (int i = 1; i < N; ++i) {
        auto it = m.lower_bound(p[i]);

        if (it == m.end() || it->second <= q[i]) {
            it = m.insert({p[i], q[i]}).first;
        } else {
            ret += m.size();
            continue;
        }

        if (it == m.begin()) {
            ret += m.size();
            continue;
        }
        it--;
        while (it->second < q[i]) {
            if (it == m.begin()) {
                m.erase(it);
                break;
            } else {
                auto jt = it;
                jt--;
                m.erase(it);
                it = jt;
            }
        }

        ret += m.size();
    }
    return ret;
}

// // 더 깔끔한 정답코드
// #include <bits/stdc++.h>
// using namespace std;

// int C, N;
// map<int, int> coords; // coords[x] = y

// // (x, y)가 기존 점들에게 지배당하는지 여부 확인
// bool isDominated(int x, int y) {
//     auto it = coords.lower_bound(x);
//     if (it == coords.end())
//         return false;      // 오른쪽에 점 없음
//     return y < it->second; // 오른쪽 점의 y가 더 크면 지배당함
// }

// // (x, y)가 추가될 때, 왼쪽에서 (x, y)에 지배당하는 점들을 제거
// void removeDominated(int x, int y) {
//     auto it = coords.lower_bound(x);
//     if (it == coords.begin())
//         return; // 왼쪽 점 없음

//     --it; // 바로 왼쪽 점부터 시작
//     while (true) {
//         if (it->second > y)
//             break; // 왼쪽 점의 y가 더 크면 종료
//         if (it == coords.begin()) {
//             coords.erase(it);
//             break;
//         }
//         auto jt = it;
//         --jt;
//         coords.erase(it);
//         it = jt;
//     }
// }

// // 새로운 점 (x, y) 등록
// int registerPoint(int x, int y) {
//     if (isDominated(x, y))
//         return coords.size(); // 지배당하면 추가 안 함
//     removeDominated(x, y);    // (x, y)에 의해 지배당하는 왼쪽 점 삭제
//     coords[x] = y;            // (x, y) 등록
//     return coords.size();
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);

//     cin >> C;
//     while (C--) {
//         cin >> N;
//         coords.clear();
//         int result = 0;
//         for (int i = 0; i < N; i++) {
//             int x, y;
//             cin >> x >> y;
//             result += registerPoint(x, y);
//         }
//         cout << result << "\n";
//     }
//     return 0;
// }