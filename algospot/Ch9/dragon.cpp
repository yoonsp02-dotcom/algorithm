#include <bits/stdc++.h>

using namespace std;

const int MAX = 1 * 1000 * 1000 * 1000 + 100;
const string Xnext = "X+YF", Ynext = "FX-Y";
int C, N, P, l, skip;
string X[5], Y[5];
void makeXY();
string ans(int n, const string form);
string dragon(int n, const string form);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    makeXY();
    cin >> C;
    while (C--) {
        cin >> N >> P >> l;
        skip = P - 1;
        if (N == 0) {
            if (l == 2) {
                cout << "FX" << "\n";
                continue;
            }
            if (P == 0) {
                cout << "F" << "\n";
                continue;
            }
            cout << "X" << "\n";
            continue;
        }
        cout << dragon(N, "FX+YF") << "\n";
    }

    return 0;
}

void makeXY() {
    X[0] = "X";
    Y[0] = "Y";
    for (int i = 1; i < 5; ++i) {
        X[i] = X[i - 1] + "+" + Y[i - 1] + "F";
        Y[i] = "F" + X[i - 1] + "-" + Y[i - 1];
    }
}

string ans(int n, const string form) {
    // cout << "ans " << n << " l: " << l << endl;
    string ret = "";
    for (int i = 0; i < form.size() && l > 0; ++i) {
        if (form[i] != 'X' && form[i] != 'Y') {
            ret += form[i];
            l--;
            continue;
        }

        int potentialLen = (n < 29) ? pow(2, n - 1) * 3 - 2 : MAX;
        if (potentialLen > l) {
            string next = (form[i] == 'X') ? Xnext : Ynext;
            ret += ans(n - 1, next);
            break;
        } else if (form[i] == 'X') {
            ret += X[n - 1];
        } else if (form[i] == 'Y') {
            ret += Y[n - 1];
        }
        l -= potentialLen;
    }
    // cout << "ans " << n << " ret: " << ret << endl;
    return ret;
}

string dragon(int n, const string form) {
    // cout << "dragon " << n  << " skip: " << skip << " form: " << form <<
    // endl;
    string ret = "";
    for (int i = 0; i < form.size() && l > 0; ++i) {
        if (skip == 0) {
            ret += ans(n, form.substr(i));
            break;
        }
        if (form[i] != 'X' && form[i] != 'Y') {
            skip--;
            continue;
        }

        int potentialLen = (n < 29) ? pow(2, n - 1) * 3 - 2 : MAX;
        if (potentialLen <= skip) {
            skip -= potentialLen;
        } else {
            string next = (form[i] == 'X') ? Xnext : Ynext;
            ret += dragon(n - 1, next);
        }
    }
    // cout << "dragon " << n << " ret: " << ret << endl;
    return ret;
}