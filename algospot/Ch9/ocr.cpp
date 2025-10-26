#include <bits/stdc++.h>

#define MX_M 500
#define MX_N 100

using namespace std;

int m, q, n;
double B[MX_M];
double T[MX_M][MX_M], M[MX_M][MX_M];
double cache[MX_M][MX_N];
int choice[MX_M][MX_N];
string words[MX_M];
vector<int> sen;

double highestProb(int prev, int idx);
string reconstruct(int prev, int idx);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 0; i < MX_M; ++i) {
        B[i] = 0;
        for (int j = 0; j < MX_M; ++j) {
            T[i][j] = 0;
            M[i][j] = 0;
        }
    }

    cin >> m >> q;
    for (int i = 0; i < m; ++i)
        cin >> words[i];
    for (int i = 0; i < m; ++i) {
        cin >> B[i];
        B[i] = log(B[i]);
    }
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> T[i][j];
            T[i][j] = log(T[i][j]);
        }
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> M[i][j];
            M[i][j] = log(M[i][j]);
        }

    while (q--) {
        for (int i = 0; i < MX_M; ++i)
            for (int j = 0; j < MX_N; ++j)
                cache[i][j] = 1.0;

        cin >> n;
        sen = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            string str;
            cin >> str;
            for (int j = 0; j < m; ++j) {
                if (words[j] == str) {
                    sen[i] = j;
                    break;
                }
            }
        }

        highestProb(0, 0);
        cout << reconstruct(0, 0) << "\n";
    }

    return 0;
}

double highestProb(int prev, int idx) {
    if (idx == n)
        return 0;

    int wordIdx = sen[idx];
    double &ret = cache[prev][idx];
    if (ret != 1.0)
        return ret;

    ret = -1e200;
    int &choose = choice[prev][idx];
    for (int ori = 0; ori < m; ++ori) {
        double cand;
        if (idx == 0) {
            cand = M[ori][wordIdx] + B[ori] + highestProb(ori, idx + 1);
        } else {
            cand = M[ori][wordIdx] + T[prev][ori] + highestProb(ori, idx + 1);
        }

        if (ret < cand) {
            ret = cand;
            choose = ori;
        }
    }
    return ret;
}

string reconstruct(int prev, int idx) {
    int origin = choice[prev][idx];
    string ret = words[origin];
    if (idx == n - 1)
        return ret;
    ret = ret + " " + reconstruct(origin, idx + 1);
    return ret;
}