#include <bits/stdc++.h>

using namespace std;

int C, n;

vector<double> diff(const vector<double> &poly);          // 다항식 미분
double evaluate(const vector<double> &poly, double x);    // 다항식 값 계산
vector<double> solveEquation(const vector<double> &poly); // 방정식의 실근 찾기

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> n;
        vector<double> poly(n + 1);
        // poly[i]는 x^i 항의 계수
        for (int i = n; i >= 0; --i)
            cin >> poly[i];
        vector<double> ans = solveEquation(poly);
        cout << fixed;
        cout.precision(12);
        for (double n : ans)
            cout << n << " ";
        cout << "\n";
    }

    return 0;
}

vector<double> diff(const vector<double> &poly) {
    vector<double> ret(poly.size() - 1);
    for (int i = 1; i < poly.size(); ++i) {
        ret[i - 1] = i * poly[i];
    }
    return ret;
}

double evaluate(const vector<double> &poly, double x) {
    double ret = 0;
    for (int i = 0; i < poly.size(); ++i) {
        ret += poly[i] * pow(x, i);
    }
    return ret;
}

vector<double> solveEquation(const vector<double> &poly) {
    // poly가 1차식일 경우 직접 근 계산하여 반환
    if (poly.size() == 2)
        return vector<double>(1, -poly[0] / poly[1]);
    // 극값(꼭짓점) 후보를 구함
    vector<double> extp = diff(poly);
    // 미분된 다항식의 실근(극점)을 재귀적으로 구함
    vector<double> sols = solveEquation(extp);
    sols.insert(sols.begin(), -11);
    sols.insert(sols.end(), 11);
    vector<double> ret;
    for (int i = 0; i + 1 < sols.size(); ++i) {
        double x1 = sols[i], x2 = sols[i + 1];
        double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
        if (y1 * y2 > 0)
            continue;

        for (int it = 0; it < 100; ++it) {
            double mx = (x1 + x2) / 2;
            double my = evaluate(poly, mx);
            if (y1 * my > 0) {
                x1 = mx;
                y1 = my;
            } else {
                x2 = mx;
                y2 = my;
            }
        }
        ret.push_back((x1 + x2) / 2);
    }
    sort(ret.begin(), ret.end());
    return ret;
}