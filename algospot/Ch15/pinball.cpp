#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-9;
const double INFTY = 1e200;
int C, N;
int radius[50];

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
vector2 center[50];

vector<double> solve2(double a, double b, double c);
double hitCircle(vector2 here, vector2 dir, vector2 center, int radius);
vector2 reflect(vector2 dir, vector2 center, vector2 contact);
void simulate(vector2 here, vector2 dir);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int x, y, dx, dy;
        cin >> x >> y >> dx >> dy >> N;
        for (int i = 0; i < N; ++i) {
            cin >> center[i].x >> center[i].y >> radius[i];
        }
        vector2 here(x, y);
        vector2 dir(dx, dy);
        simulate(here, dir);
    }

    return 0;
}

vector<double> solve2(double a, double b, double c) {
    double d = b * b - 4 * a * c;
    if (d < -EPSILON)
        return vector<double>();
    if (d < EPSILON)
        return vector<double>(1, -b / (2 * a));
    vector<double> ret;
    ret.push_back((-b - sqrt(d)) / (2 * a));
    ret.push_back((-b + sqrt(d)) / (2 * a));
    return ret;
}

double hitCircle(vector2 here, vector2 dir, vector2 center, int radius) {
    double a = dir.dot(dir);
    double b = 2 * dir.dot(here - center);
    double c = center.dot(center) + here.dot(here) - 2 * here.dot(center) -
               radius * radius;
    vector<double> sols = solve2(a, b, c);
    if (sols.empty() || sols[0] < EPSILON)
        return INFTY;
    return sols[0];
}

vector2 reflect(vector2 dir, vector2 center, vector2 contact) {
    return (dir - dir.project(contact - center) * 2).normalize();
}

void simulate(vector2 here, vector2 dir) {
    dir = dir.normalize();
    int hitcount = 0;
    while (hitcount < 100) {
        int circle = -1;
        double t = INFTY * 0.5;
        for (int i = 0; i < N; ++i) {
            double cand = hitCircle(here, dir, center[i], radius[i] + 1);
            if (cand < t) {
                t = cand;
                circle = i;
            }
        }
        if (circle == -1)
            break;
        if (hitcount++)
            cout << " ";
        cout << circle;
        vector2 contact = here + dir * t;
        dir = reflect(dir, center[circle], contact);
        here = contact;
    }
    cout << "\n";
}