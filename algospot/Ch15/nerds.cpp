#include <bits/stdc++.h>
using namespace std;

const double PI = 2.0 * acos(0.0);
const double EPSILON = 1e-9;

int C, N;

// 2차원 벡터 구조체 정의
struct vector2 {
    double x, y;

    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

    bool operator==(const vector2 &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator<(const vector2 &rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }

    vector2 operator+(const vector2 &rhs) const {
        return vector2(x + rhs.x, y + rhs.y);
    }

    vector2 operator-(const vector2 &rhs) const {
        return vector2(x - rhs.x, y - rhs.y);
    }

    vector2 operator*(double rhs) const { return vector2(x * rhs, y * rhs); }

    double norm() const { return hypot(x, y); }

    vector2 normalize() const { return vector2(x / norm(), y / norm()); }

    double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }

    double dot(const vector2 &rhs) const { return x * rhs.x + y * rhs.y; }

    double cross(const vector2 &rhs) const { return x * rhs.y - rhs.x * y; }
};

typedef vector<vector2> polygon;

// ccw: 반시계 방향 판단 (외적 활용)
double ccw(vector2 a, vector2 b) { return a.cross(b); }
double ccw(vector2 p, vector2 a, vector2 b) { return ccw(a - p, b - p); }

// 두 선분이 교차하는지 확인
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
    double ab = ccw(a, b, c) * ccw(a, b, d);
    double cd = ccw(c, d, a) * ccw(c, d, b);

    if (ab == 0 && cd == 0) {
        if (b < a)
            swap(a, b);
        if (d < c)
            swap(c, d);
        return !(b < c || d < a); // 선분이 겹치는 경우
    }
    return ab <= 0 && cd <= 0;
}

// 점 q가 다각형 p 안에 있는지 확인
bool isInside(vector2 q, const polygon &p) {
    int crosses = 0;
    for (int i = 0; i < p.size(); ++i) {
        int j = (i + 1) % p.size();
        if ((p[i].y > q.y) != (p[j].y > q.y)) {
            double atX =
                (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
            if (q.x < atX)
                ++crosses;
        }
    }
    return crosses % 2 > 0; // 홀수 교차면 내부
}

// 선물 포장 알고리즘으로 볼록 껍질 계산
polygon giftWrap(const vector<vector2> points) {
    int n = points.size();
    polygon hull;
    vector2 pivot =
        *min_element(points.begin(), points.end()); // 가장 왼쪽 아래 점
    hull.push_back(pivot);

    while (true) {
        vector2 ph = hull.back();
        vector2 next = points[0];
        for (int i = 1; i < n; ++i) {
            double cross = ccw(ph, next, points[i]);
            double dist = (ph - next).norm() - (ph - points[i]).norm();
            if (cross > 0 || (cross == 0 && dist < 0))
                next = points[i];
        }
        if (next == pivot)
            break;
        hull.push_back(next);
    }
    return hull;
}

// 두 다각형이 겹치는지 확인
bool polygonIntersects(const polygon &p, const polygon &q) {
    int n = p.size(), m = q.size();
    // 한 다각형이 다른 다각형 내부에 있는 경우
    if (isInside(p[0], q) || isInside(q[0], p))
        return true;

    // 두 다각형의 변이 교차하는지 확인
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (segmentIntersects(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
                return true;

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int n;
        cin >> n;

        vector<polygon> groups(2); // 0: non-nerd, 1: nerd

        for (int i = 0; i < n; ++i) {
            int type, x, y;
            cin >> type >> x >> y;
            groups[type].push_back(vector2(x, y));
        }

        polygon hull0 = giftWrap(groups[0]);
        polygon hull1 = giftWrap(groups[1]);

        // 두 볼록 다각형이 겹치지 않으면 이론 성립
        if (!polygonIntersects(hull0, hull1))
            cout << "THEORY HOLDS\n";
        else
            cout << "THEORY IS INVALID\n";
    }

    return 0;
}
