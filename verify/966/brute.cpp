#include <bits/stdc++.h>
using namespace std;

// 暴力参考解：与 std.cpp 使用相同的"圆盘∩三角形"交集面积公式，
// 但最大化方式改为二维网格采样（独立于 std 的三分搜索），用于对拍。

const double PI = acos(-1.0);

struct Pt { double x, y; };
Pt operator-(Pt a, Pt b) { return {a.x - b.x, a.y - b.y}; }
double cross(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
double dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
double len(Pt a) { return hypot(a.x, a.y); }

double norm_angle(double t) {
    while (t > PI) t -= 2 * PI;
    while (t <= -PI) t += 2 * PI;
    return t;
}

double triangle_area(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    return sqrt(max(0.0, s * (s - a) * (s - b) * (s - c)));
}

vector<Pt> triangle_vertices(double a, double b, double c) {
    double x = (b * b + c * c - a * a) / (2.0 * c);
    double y = sqrt(max(0.0, b * b - x * x));
    return {{0.0, 0.0}, {c, 0.0}, {x, y}};
}

double wedge_disk_area(Pt p, Pt q, double R) {
    double cr = cross(p, q);
    if (fabs(cr) < 1e-14) return 0.0;
    Pt d = q - p;
    double dl = len(d);
    Pt n = {d.y / dl, -d.x / dl};
    if (dot(n, p) < 0.0) { n.x = -n.x; n.y = -n.y; }
    double h = dot(n, p);
    double thn = atan2(n.y, n.x);
    double thp = atan2(p.y, p.x), thq = atan2(q.y, q.x);
    double diff = norm_angle(thq - thp);
    double lo, hi;
    if (diff >= 0) { lo = thp; hi = thp + diff; }
    else { lo = thq; hi = thq - diff; }
    double length = hi - lo;
    double integral;
    if (h >= R) {
        integral = R * R * length;
    } else {
        double gamma = acos(h / R);
        double ilo = max(lo, thn - gamma);
        double ihi = min(hi, thn + gamma);
        double inner = 0.0;
        if (ihi > ilo) inner = h * h * (tan(ihi - thn) - tan(ilo - thn));
        double outer = R * R * (length - (ihi - ilo));
        integral = inner + outer;
    }
    return 0.5 * integral;
}

double intersect_area(Pt O, double R, const vector<Pt>& V) {
    double total = 0.0;
    for (int i = 0; i < 3; i++) {
        Pt p = V[i] - O, q = V[(i + 1) % 3] - O;
        total += wedge_disk_area(p, q, R);
    }
    return total;
}

bool inside(const vector<Pt>& V, double x, double y) {
    for (int i = 0; i < 3; i++) {
        Pt A = V[i], B = V[(i + 1) % 3];
        if ((B.x - A.x) * (y - A.y) - (B.y - A.y) * (x - A.x) < -1e-12) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, c;
    if (!(cin >> a >> b >> c)) return 1;

    vector<Pt> V = triangle_vertices(a, b, c);
    double A = triangle_area(a, b, c);
    double R = sqrt(A / PI);

    double xlo = min({V[0].x, V[1].x, V[2].x});
    double xhi = max({V[0].x, V[1].x, V[2].x});
    double ylo = min({V[0].y, V[1].y, V[2].y});
    double yhi = max({V[0].y, V[1].y, V[2].y});

    // 两级网格：先粗后细
    double best = -1.0;
    auto scan = [&](double step) {
        for (double y = ylo; y <= yhi + 1e-12; y += step)
            for (double x = xlo; x <= xhi + 1e-12; x += step)
                if (inside(V, x, y)) best = max(best, intersect_area({x, y}, R, V));
    };
    scan(0.02);
    scan(0.002);

    cout << fixed << setprecision(6) << best << "\n";
    return 0;
}
