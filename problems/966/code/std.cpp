#include <bits/stdc++.h>
using namespace std;

// PE 966: Triangle Circle Intersection / 三角形与圆的交集  —— 简单(缩数据)版
//
// I(a,b,c) = 边长 a,b,c 的三角形 与 面积相同的圆 的最大交集面积。
// 圆面积 = 三角形面积 A，故圆半径 R = sqrt(A / PI)。
// 问题：把圆放在平面任意位置，使其与三角形的重叠面积最大。
//
// 原题要求对所有满足 1<=a<=b<=c<a+b 且 a+b+c<=200 的整数三角形求和。
// 本"简单版"缩数据为：读入单个三角形 (a,b,c)，输出 I(a,b,c)（保留 6 位小数）。
//
// 算法：
//   1. 三角形面积 A 用海伦公式，R = sqrt(A/PI)。
//   2. 把三角形置于坐标平面（A=(0,0), B=(c,0), C=(x,y)，逆时针）。
//   3. 求"圆盘(圆心 O, 半径 R) 与三角形"的交集面积 f(O)：
//      设圆心 O 在三角形内部，用 O 到三个顶点的扇形剖分：
//        交面积 = Σ_i 三角形(O, V_i, V_{i+1}) ∩ 圆盘 的面积。
//      单个"扇形三角形(O,p,q) ∩ 圆盘"用径向积分：
//        f = (1/2) ∫_{θ_p}^{θ_q} min(R^2, (h/cos(φ-φ_n))^2) dφ
//      其中 h 是 O 到边 pq 的距离，φ_n 是 O 指向边 pq 的法向方向角。
//      当 h>=R 时积分 = R^2*角度；否则在 |φ-φ_n|<arccos(h/R) 区间积 h^2/cos^2，
//      其余区间积 R^2。h^2/cos^2 的原函数是 h^2*tan(φ-φ_n)。
//   4. f(O) 是 log-concave（两个凸集指示函数的卷积），故单峰。
//      对 x 做外层三分、对 y 做内层三分（y 限制在三角形在该 x 处的竖直截面内），
//      求得全局最大值 = I(a,b,c)。
//
// 验证点：I(3,4,5) ≈ 4.593049, I(3,4,6) ≈ 3.552564。

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

// 三角形面积（海伦公式）
double triangle_area(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    return sqrt(max(0.0, s * (s - a) * (s - b) * (s - c)));
}

// 边长为 a,b,c 的三角形顶点（逆时针）：
//   A=(0,0), B=(c,0), C=(x,y)，其中 x=(b^2+c^2-a^2)/(2c), y=sqrt(b^2-x^2)
vector<Pt> triangle_vertices(double a, double b, double c) {
    double x = (b * b + c * c - a * a) / (2.0 * c);
    double y = sqrt(max(0.0, b * b - x * x));
    return {{0.0, 0.0}, {c, 0.0}, {x, y}};
}

// 圆盘(圆心原点, 半径 R) 与三角形(O, p, q) 的交集面积（正），p,q 为相对 O 的向量。
// 用小张角扇形的径向积分。
double wedge_disk_area(Pt p, Pt q, double R) {
    double cr = cross(p, q);
    if (fabs(cr) < 1e-14) return 0.0;
    // O 指向边 pq 的单位法向 n（n·p > 0）
    Pt d = q - p;
    double dl = len(d);
    Pt n = {d.y / dl, -d.x / dl};
    if (dot(n, p) < 0.0) { n.x = -n.x; n.y = -n.y; }
    double h = dot(n, p);           // O 到边 pq 的距离
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
        double gamma = acos(h / R);            // arccos(h/R) in (0, PI/2)
        double ilo = max(lo, thn - gamma);
        double ihi = min(hi, thn + gamma);
        double inner = 0.0;
        if (ihi > ilo)
            inner = h * h * (tan(ihi - thn) - tan(ilo - thn));
        double outer = R * R * (length - (ihi - ilo));
        integral = inner + outer;
    }
    return 0.5 * integral;
}

// 圆盘(圆心 O, 半径 R) 与三角形 V(逆时针) 的交集面积。
// 要求 O 在三角形内部（最优圆心必在内部），此时三个扇形三角形均正。
double intersect_area(Pt O, double R, const vector<Pt>& V) {
    double total = 0.0;
    for (int i = 0; i < 3; i++) {
        Pt p = V[i] - O, q = V[(i + 1) % 3] - O;
        total += wedge_disk_area(p, q, R);
    }
    return total;
}

// 竖直线 x = X 与三角形 V 的交线的 y 区间 [ylo, yhi]；不存在返回 false。
bool vertical_span(const vector<Pt>& V, double X, double& ylo, double& yhi) {
    double lo = 1e300, hi = -1e300;
    bool found = false;
    for (int i = 0; i < 3; i++) {
        Pt A = V[i], B = V[(i + 1) % 3];
        if (fabs(A.x - B.x) < 1e-15) {
            if (fabs(X - A.x) < 1e-12) {
                lo = min(lo, min(A.y, B.y));
                hi = max(hi, max(A.y, B.y));
                found = true;
            }
        } else {
            double xmin = min(A.x, B.x), xmax = max(A.x, B.x);
            if (X >= xmin - 1e-12 && X <= xmax + 1e-12) {
                double y = A.y + (B.y - A.y) * (X - A.x) / (B.x - A.x);
                lo = min(lo, y);
                hi = max(hi, y);
                found = true;
            }
        }
    }
    if (!found) return false;
    ylo = lo; yhi = hi;
    return true;
}

// I(a,b,c)：对圆心做二维三分搜索（x 外层，y 内层）。
double solve_I(double a, double b, double c) {
    vector<Pt> V = triangle_vertices(a, b, c);
    double A = triangle_area(a, b, c);
    double R = sqrt(A / PI);
    double xlo = min({V[0].x, V[1].x, V[2].x});
    double xhi = max({V[0].x, V[1].x, V[2].x});

    // g(x) = max_y f(x,y)
    auto g = [&](double x) -> double {
        double ylo, yhi;
        if (!vertical_span(V, x, ylo, yhi)) return -1e300;
        double l = ylo, r = yhi;
        for (int it = 0; it < 70; it++) {
            double m1 = l + (r - l) / 3.0, m2 = r - (r - l) / 3.0;
            double f1 = intersect_area({x, m1}, R, V);
            double f2 = intersect_area({x, m2}, R, V);
            if (f1 < f2) l = m1; else r = m2;
        }
        return intersect_area({x, (l + r) / 2.0}, R, V);
    };

    double l = xlo, r = xhi;
    for (int it = 0; it < 70; it++) {
        double m1 = l + (r - l) / 3.0, m2 = r - (r - l) / 3.0;
        double g1 = g(m1), g2 = g(m2);
        if (g1 < g2) l = m1; else r = m2;
    }
    return g((l + r) / 2.0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, c;
    if (!(cin >> a >> b >> c)) {
        cerr << "Usage: 输入三个整数 a b c (三角形三边)，输出 I(a,b,c)\n";
        cerr << "示例: 输入 \"3 4 5\" 输出 4.593049\n";
        return 1;
    }

    double ans = solve_I(a, b, c);
    cout << fixed << setprecision(6) << ans << "\n";
    return 0;
}
