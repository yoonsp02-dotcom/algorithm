#include <bits/stdc++.h>

using namespace std;

int c, n;
vector<int> height;
vector<int> l;
vector<int> r;
int maxSquare();

int main() {
    cin >> c;
    while (c--) {
        cin >> n;
        height = vector<int>(n + 1, 0);
        l = vector<int>(n + 1, 0);
        r = vector<int>(n + 1, 0);
        for (int i = 0; i < n; ++i)
            cin >> height[i];
        height[n] = 0;
        cout << maxSquare() << "\n";
    }

    return 0;
}

int maxSquare() {
    stack<int> st;
    for (int i = 0; i < height.size(); ++i) {
        while (!st.empty() && height[i] < height[st.top()]) {
            int t = st.top();
            st.pop();
            r[t] = i - 1;
        }

        if (st.empty()) {
            l[i] = 0;
            st.push(i);
        } else if (height[i] > height[st.top()]) {
            l[i] = st.top() + 1;
            st.push(i);
        } else {
            l[i] = l[st.top()];
            st.push(i);
        }
    }

    int ret = 0;
    for (int i = 0; i < height.size(); ++i) {
        ret = max(ret, (r[i] - l[i] + 1) * height[i]);
    }
    return ret;
}

// solved by divied and conquer
// #include <bits/stdc++.h>

// using namespace std;

// int c, n;
// vector<int> h;

// int maxSquare(int left, int right);

// int main() {
//     cin >> c;
//     while (c--) {
//         cin >> n;
//         h = vector<int>(n, 0);
//         for (int i = 0; i < n; ++i)
//             cin >> h[i];

//         cout << maxSquare(0, h.size() - 1) << "\n";
//     }

//     return 0;
// }

// int maxSquare(int left, int right) {
//     if (left == right)
//         return h[left];

//     int half = (left + right) / 2;
//     int ret = maxSquare(left, half);
//     ret = max(ret, maxSquare(half + 1, right));

//     int height = min(h[half], h[half + 1]);
//     ret = max(ret, 2 * height);

//     int l = half, r = half + 1;
//     while (left < l || r < right) {
//         if (r < right && (l == left || h[r + 1] >= h[l - 1])) {
//             ++r;
//             height = min(height, h[r]);
//         } else {
//             --l;
//             height = min(height, h[l]);
//         }
//         ret = max(ret, (r - l + 1) * height);
//     }

//     return ret;
// }