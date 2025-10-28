#include <bits/stdc++.h>

using namespace std;

int C;
// 원주율 π (PI = 3.14159...)
const double PI = 2.0 * acos(0.0);
const double EPSILON = 1e-9;

// 2차원 벡터(또는 점)를 표현하는 구조체
struct vector2 {
    double x, y;

    // 생성자 (기본값은 (0, 0))
    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

    // 벡터 비교 (x와 y가 모두 같을 때만 true)
    bool operator==(const vector2 &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    // 사전순 비교 (x 우선, x가 같으면 y 비교)
    bool operator<(const vector2 &rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }

    // 벡터 덧셈
    vector2 operator+(const vector2 &rhs) const {
        return vector2(x + rhs.x, y + rhs.y);
    }

    // 벡터 뺄셈
    vector2 operator-(const vector2 &rhs) const {
        return vector2(x - rhs.x, y - rhs.y);
    }

    // 스칼라 곱셈
    vector2 operator*(double rhs) const { return vector2(x * rhs, y * rhs); }

    // 벡터의 크기(길이)
    double norm() const {
        return hypot(x, y); // sqrt(x^2 + y^2)
    }

    // 단위 벡터로 변환
    vector2 normalize() const { return vector2(x / norm(), y / norm()); }

    // 벡터의 극각(방향)을 [0, 2π) 범위로 반환
    double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }

    // 내적 (dot product)
    double dot(const vector2 &rhs) const { return x * rhs.x + y * rhs.y; }

    // 외적 (cross product, 면적 및 방향성 판단에 사용)
    double cross(const vector2 &rhs) const { return x * rhs.y - rhs.x * y; }

    // 벡터 rhs에 vector2 자신을 정사영(projection)
    vector2 project(const vector2 &rhs) const {
        vector2 r = rhs.normalize();
        return r * r.dot(*this);
    }
};
typedef vector<vector2> polygon;

double ccw(vector2 a, vector2 b);
double ccw(vector2 p, vector2 a, vector2 b);
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 &x);
// (a, b)를 포함하는 직선으로 다각현 p를 자른 뒤, (a, b)의 왼쪽에 있는 부분들을
// 반환한다.
polygon cutPoly(const polygon &p, const vector2 &a, const vector2 &b);
polygon intersection(const polygon &p, double x1, double y1, double x2,
                     double y2);
double area(const polygon &p);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int x1, y1, x2, y2, n;
        cin >> x1 >> y1 >> x2 >> y2 >> n;
        polygon p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }
        cout << fixed;
        cout.precision(10);
        cout << area(intersection(p, x1, y1, x2, y2)) << "\n";
    }

    return 0;
}

polygon cutPoly(const polygon &p, const vector2 &a, const vector2 &b) {
    int n = p.size();
    vector<bool> inside(n);
    for (int i = 0; i < n; ++i)
        inside[i] = (ccw(a, b, p[i]) >= 0);

    polygon ret;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (inside[i])
            ret.push_back(p[i]);
        if (inside[i] != inside[j]) {
            vector2 cross;
            assert(lineIntersection(p[i], p[j], a, b, cross));
            ret.push_back(cross);
        }
    }
    return ret;
}

polygon intersection(const polygon &p, double x1, double y1, double x2,
                     double y2) {
    vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
    polygon ret = cutPoly(p, a, b);
    ret = cutPoly(ret, b, c);
    ret = cutPoly(ret, c, d);
    ret = cutPoly(ret, d, a);
    return ret;
}

double area(const polygon &p) {
    double ret = 0;
    for (int i = 0; i < p.size(); ++i) {
        int j = (i + 1) % p.size();
        ret += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return fabs(ret) / 2.0;
}

double ccw(vector2 a, vector2 b) { return a.cross(b); }

double ccw(vector2 p, vector2 a, vector2 b) { return ccw(a - p, b - p); }

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 &x) {
    double det = (b - a).cross(d - c);
    if (fabs(det) < EPSILON)
        return false;
    x = a + (b - a) * ((c - a).cross(d - c) / det);
    return true;
}