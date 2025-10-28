#include <bits/stdc++.h>

using namespace std;

int C;

struct point {
    double x, y;
};
vector<point> hull1, hull2;
vector<pair<point, point>> upper, lower;

// 각 볼록 껍질을 상단과 하단 선분으로 분해
void decompose(const vector<point> &hull);
// 주어진 x 좌표가 선분 (a, b) 사이에 있는지 확인
bool between(const point &a, const point &b, double x);
// 선분 (a, b)위의 x좌표에 대한 y값을 반환
double at(const point &a, const point &b, double x);
double vertical(double x);
double minX(const vector<point> &hull);
double maxX(const vector<point> &hull);
double fossil();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        hull1.clear();
        hull2.clear();
        upper.clear();
        lower.clear();
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            point dot;
            cin >> dot.x >> dot.y;
            hull1.push_back(dot);
        }
        for (int i = 0; i < m; i++) {
            point dot;
            cin >> dot.x >> dot.y;
            hull2.push_back(dot);
        }
        decompose(hull1);
        decompose(hull2);
        cout << fixed;
        cout.precision(8);
        cout << fossil() << endl;
    }

    return 0;
}

void decompose(const vector<point> &hull) {
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        if (hull[i].x < hull[(i + 1) % n].x)
            lower.push_back(make_pair(hull[i], hull[(i + 1) % n]));
        else if (hull[i].x > hull[(i + 1) % n].x)
            upper.push_back(make_pair(hull[i], hull[(i + 1) % n]));
    }
}

bool between(const point &a, const point &b, double x) {
    return ((a.x <= x && b.x >= x) || (a.x >= x && b.x <= x));
}

double at(const point &a, const point &b, double x) {
    double dy = b.y - a.y, dx = b.x - a.x;
    return dy / dx * (x - a.x) + a.y;
}

double vertical(double x) {
    double minUp = 1e20, maxLow = -1e20;
    for (int i = 0; i < upper.size(); i++)
        if (between(upper[i].first, upper[i].second, x))
            minUp = min(minUp, at(upper[i].first, upper[i].second, x));
    for (int i = 0; i < lower.size(); i++)
        if (between(lower[i].first, lower[i].second, x))
            maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
    return minUp - maxLow;
}

double minX(const vector<point> &hull) {
    double ret = 1e20;
    for (int i = 0; i < hull.size(); i++)
        ret = min(ret, hull[i].x);
    return ret;
}

double maxX(const vector<point> &hull) {
    double ret = -1e20;
    for (int i = 0; i < hull.size(); i++)
        ret = max(ret, hull[i].x);
    return ret;
}

double fossil() {
    double lo = max(minX(hull1), minX(hull2));
    double hi = min(maxX(hull1), maxX(hull2));
    if (hi < lo)
        return 0;
    for (int i = 0; i < 100; i++) {
        double aab = (lo * 2 + hi) / 3.0;
        double abb = (lo + hi * 2) / 3.0;
        if (vertical(aab) < vertical(abb))
            lo = aab;
        else
            hi = abb;
    }
    return max(0.0, vertical(hi));
}