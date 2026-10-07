// 935 扫描 v3: 吸附到 1/q 格点 (理论: 有理 b=p/q 的所有接触点在 1/q 格点上)
#include <bits/stdc++.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;
using ll = long long;
static double SNAP; // 格点间距 1/q
struct Pt { double x, y; };
static void snap(Pt& p) { p.x = llround(p.x / SNAP) * SNAP; p.y = llround(p.y / SNAP) * SNAP; }
static bool onBottom(const Pt& p) { return fabs(p.y) < 1e-9; }
static bool onTop(const Pt& p) { return fabs(p.y - 1) < 1e-9; }
static bool onLeft(const Pt& p) { return fabs(p.x) < 1e-9; }
static bool onRight(const Pt& p) { return fabs(p.x - 1) < 1e-9; }
static bool onBoundary(const Pt& p) { return onBottom(p) || onTop(p) || onLeft(p) || onRight(p); }
static bool feasible(Pt* c, int pv) {
    for (int j = 0; j < 4; j++) {
        if (j == pv || !onBoundary(c[j])) continue;
        double dx = c[j].x - c[pv].x, dy = c[j].y - c[pv].y;
        double vx = dy, vy = -dx;
        auto check = [&](double nx, double ny) { return !(vx * nx + vy * ny > 1e-12); };
        if (onBottom(c[j]) && !check(0, -1)) return false;
        if (onTop(c[j]) && !check(0, 1)) return false;
        if (onLeft(c[j]) && !check(-1, 0)) return false;
        if (onRight(c[j]) && !check(1, 0)) return false;
    }
    return true;
}
// 返回首回归步数; -1 = 不回归/异常
ll simulate(double b, ll q, ll maxsteps) {
    SNAP = 1.0 / (double)q;
    Pt c[4] = {{0, 0}, {b, 0}, {b, b}, {0, b}};
    int pivot = 1;
    vector<double> sig;
    for (int i = 0; i < 4; i++) sig.push_back(c[i].x * 3.0 + c[i].y);
    sort(sig.begin(), sig.end());
    for (ll step = 1; step <= maxsteps; step++) {
        double px = c[pivot].x, py = c[pivot].y;
        double best = 1e18;
        vector<int> landers;
        for (int k = 0; k < 4; k++) {
            if (k == pivot) continue;
            double dx = c[k].x - px, dy = c[k].y - py;
            double r = sqrt(dx * dx + dy * dy);
            double th0 = atan2(dy, dx);
            double dk = 1e18;
            auto consider = [&](double qx, double qy) {
                if (qx < -1e-12 || qx > 1 + 1e-12 || qy < -1e-12 || qy > 1 + 1e-12) return;
                double th = atan2(qy - py, qx - px);
                double d = fmod(th0 - th, 2 * M_PI);
                if (d < 0) d += 2 * M_PI;
                if (d > 1e-12 && d < dk) dk = d;
            };
            if (r >= py) { double t = sqrt(max(0.0, r*r - py*py)); consider(px + t, 0); consider(px - t, 0); }
            if (r >= 1 - py) { double t = sqrt(max(0.0, r*r - (1-py)*(1-py))); consider(px + t, 1); consider(px - t, 1); }
            if (r >= px) { double t = sqrt(max(0.0, r*r - px*px)); consider(0, py + t); consider(0, py - t); }
            if (r >= 1 - px) { double t = sqrt(max(0.0, r*r - (1-px)*(1-px))); consider(1, py + t); consider(1, py - t); }
            if (dk < 1e17) {
                if (dk < best - 1e-12) { best = dk; landers.clear(); landers.push_back(k); }
                else if (fabs(dk - best) < 1e-12) landers.push_back(k);
            }
        }
        if (landers.empty()) return -1;
        {
            double s = sin(-best), co = cos(-best);
            for (int i = 0; i < 4; i++) {
                if (i == pivot) continue;
                double dx = c[i].x - px, dy = c[i].y - py;
                c[i].x = px + dx * co - dy * s;
                c[i].y = py + dx * s + dy * co;
            }
            for (int i = 0; i < 4; i++) snap(c[i]);
        }
        {
            vector<double> v;
            for (int i = 0; i < 4; i++) v.push_back(c[i].x * 3.0 + c[i].y);
            sort(v.begin(), v.end());
            bool ok = true;
            for (int i = 0; i < 4; i++) if (fabs(v[i] - sig[i]) > 1e-9) ok = false;
            if (ok) return step;
        }
        int np = -1;
        for (int k : landers) if (feasible(c, k)) { np = k; break; }
        if (np < 0) {
            double ba = -1;
            auto peri = [](const Pt& p) -> double {
                if (onBottom(p)) return p.x;
                if (onRight(p)) return 1 + p.y;
                if (onTop(p)) return 2 + (1 - p.x);
                if (onLeft(p)) return 3 + (1 - p.y);
                return -1;
            };
            for (int k = 0; k < 4; k++) {
                if (!onBoundary(c[k]) || !feasible(c, k)) continue;
                double a = peri(c[k]);
                if (a > ba) { ba = a; np = k; }
            }
        }
        if (np < 0) return -1;
        pivot = np;
    }
    return -1;
}
int main(int argc, char** argv) {
    ll qmax = (argc > 1) ? atoll(argv[1]) : 30;
    ll maxsteps = (argc > 2) ? atoll(argv[2]) : 5000;
    // 统计: (q -> 该 q 下回归的 p 列表 + 步数)
    for (ll q = 2; q <= qmax; q++) {
        string ps;
        ll cnt = 0;
        for (ll p = 1; p < q; p++) {
            if (std::gcd(p, q) != 1) continue;
            ll s = simulate((double)p / q, q, maxsteps);
            if (s > 0) { cnt++; ps += " " + to_string(p) + ":" + to_string(s); }
        }
        if (cnt) printf("q=%lld cnt=%lld |%s\n", q, cnt, ps.c_str());
    }
    return 0;
}
