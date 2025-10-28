#include <bits/stdc++.h>
using namespace std;

const double EPSILON = 1e-9;

// 원주율 π (PI = 3.14159...)
const double PI = 2.0 * acos(0.0);

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
    vector2 normalize() const {
        double n = norm();
        if (n < EPSILON)
            return vector2(0, 0); // 0 벡터 처리
        return vector2(x / n, y / n);
    }

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

// 벡터 두 개의 외적
double ccw(vector2 a, vector2 b) { return a.cross(b); }

// 점 p를 기준으로 점 a, b가 이루는 방향을 외적으로 판단
// > 0: 반시계, < 0: 시계, == 0: 일직선
double ccw(vector2 p, vector2 a, vector2 b) { return ccw(a - p, b - p); }

// 두 직선 ab, cd의 교차 여부를 판단하고, 교점을 x에 저장
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 &x) {
    double det = (b - a).cross(d - c);
    if (fabs(det) < EPSILON)
        return false; // 평행하거나 일치
    x = a + (b - a) * ((c - a).cross(d - c) / det);
    return true;
}

// 두 선분이 평행하고 겹치는 부분이 있는지 확인, 있으면 p에 교점(겹치는 구간
// 시작점) 저장
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2 &p) {
    if (b < a)
        swap(a, b);
    if (d < c)
        swap(c, d);

    if (ccw(a, b, c) != 0 || b < c || d < a)
        return false;

    if (a < c)
        p = c;
    else
        p = a;
    return true;
}

// 점 p가 선분 ab의 경계 내에 있는지 확인
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b) {
    if (b < a)
        swap(a, b);
    return p == a || p == b || (a < p && p < b);
}

// 두 선분 ab, cd가 교차하면 교점 p 반환
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d,
                         vector2 &p) {
    if (!lineIntersection(a, b, c, d, p))
        return parallelSegments(a, b, c, d, p);
    return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
}

// 두 선분이 실제로 교차하는지 여부만 반환 (교점 저장 안 함)
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
    double ab = ccw(a, b, c) * ccw(a, b, d);
    double cd = ccw(c, d, a) * ccw(c, d, b);

    if (ab == 0 && cd == 0) {
        if (b < a)
            swap(a, b);
        if (d < c)
            swap(c, d);
        return !(b < c || d < a); // 두 선분이 겹치는 경우
    }
    return ab <= 0 && cd <= 0; // 서로 교차하는지 여부
}

// 점 p에서 선분 ab 위에 수직으로 내린 발의 좌표를 반환
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
    return a + (p - a).project(b - a);
}

// 점 p와 직선 ab 사이의 거리
double pointToLine(vector2 p, vector2 a, vector2 b) {
    return (p - perpendicularFoot(p, a, b)).norm();
}