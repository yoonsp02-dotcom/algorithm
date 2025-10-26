#include <bits/stdc++.h>

using namespace std;

// void normalize(vector<int>& c) {
//     for (int i = 0; i < c.size(); ++i) {
//         if (c[i] < 0) {
//             int borrow = (abs(c[i]) + 9) / 10;
//             c[i + 1] -= borrow;
//             c[i] += borrow * 10;
//         }
//         else {
//             c[i + 1] += c[i]/10;
//             c[i] %= 10;
//         }
//     }
//     while (c.size() > 1 && c.back() == 0) c.pop_back();
// }

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    vector<int> c(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++)
            c[i + j] += a[i] * b[j];
    // 	normalize(c);
    return c;
}

// a += b * (10^k)
void addTo(vector<int> &a, const vector<int> &b, int k) {
    a.resize(max(a.size(), b.size() + k));
    for (int i = 0; i < b.size(); i++)
        a[i + k] += b[i];
    // nomalize(a);
}

// a >= b인 경우에만 사용가능
// a -= b
void subFrom(vector<int> &a, const vector<int> &b) {
    for (int i = 0; i < b.size(); ++i)
        a[i] -= b[i];
    // normalize(a);
}

vector<int> karatsuba(const vector<int> &a, const vector<int> &b) {
    int an = a.size(), bn = b.size();

    if (an < bn)
        karatsuba(b, a);
    if (an == 0 || bn == 0)
        return vector<int>();
    if (an <= 50)
        return multiply(a, b);

    int half = an / 2;
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(half, b.size()));
    vector<int> b1(b.begin() + min<int>(half, b.size()), b.end());

    vector<int> z0 = karatsuba(a0, b0);
    vector<int> z2 = karatsuba(a1, b1);
    addTo(a0, a1, 0);
    addTo(b0, b1, 0);
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);

    vector<int> ret;
    addTo(ret, z0, 0);
    addTo(ret, z1, half);
    addTo(ret, z2, half + half);

    return ret;
}

int c;
int hugs(const string &m, const string &f);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> c;
    while (c--) {
        string m, f;
        cin >> m >> f;
        cout << hugs(m, f) << "\n";
    }

    return 0;
}

int hugs(const string &m, const string &f) {
    int mn = m.size(), fn = f.size();
    vector<int> members(mn), fans(fn);
    for (int i = 0; i < m.size(); ++i)
        members[mn - i - 1] = (m[i] == 'M');
    for (int i = 0; i < f.size(); ++i)
        fans[i] = (f[i] == 'M');
    vector<int> mul = karatsuba(members, fans);

    int cnt = 0;
    for (int i = mn - 1; i <= fn - 1; ++i)
        if (mul[i] == 0)
            cnt++;

    return cnt;
}