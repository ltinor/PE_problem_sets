// 扫描有理 b=p/q: 记录首次回归步数 (复用 t935_sim 的滚动逻辑, 批量)
#include <bits/stdc++.h>
using namespace std;
static const double PI = 3.14159265358979323846;
static double EPS = 1e-7;
struct Pt { double x, y; };
static bool onBottom(const Pt& p) { return fabs(p.y) < EPS; }
static bool onTop(const Pt& p) { return fabs(p.y - 1) < EPS; }
static bool onLeft(const Pt& p) { return fabs(p.x) < EPS; }
static bool onRight(const Pt& p) { return fabs(p.x - 1) < EPS; }
static bool onBoundary(const Pt& p) { return onBottom(p) || onTop(p) || onLeft(p) || onRight(p); }
static bool feasible(Pt* c, int pv) {
    for (int j = 0; j < 4; j++) {
        if (j == pv || !onBoundary(c[j])) continue;
        double dx = c[j].x - c[pv].x, dy = c[j].y - c[pv].y;
        double vx = dy, vy = -dx;
        auto check = [&](double nx, double ny) { return !(vx * nx + vy * ny > 1e-6); };
        if (onBottom(c[j]) && !check(0, -1)) return false;
        if (onTop(c[j]) && !check(0, 1)) return false;
        if (onLeft(c[j]) && !check(-1, 0)) return false;
        if (onRight(c[j]) && !check(1, 0)) return false;
    }
    return true;
}
// 返回首次回归步数, 不回归/卡死返回 -1
int simulate(double b, int maxsteps) {
    Pt c[4] = {{0, 0}, {b, 0}, {b, b}, {0, b}};
    int pivot = 1;
    vector<double> initSig;
    for (int i = 0; i < 4; i++) initSig.push_back(c[i].x * 3.0 + c[i].y);
    sort(initSig.begin(), initSig.end());
    for (int step = 1; step <= maxsteps; step++) {
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
                if (qx < -EPS || qx > 1 + EPS || qy < -EPS || qy > 1 + EPS) return;
                double th = atan2(qy - py, qx - px);
                double d = fmod(th0 - th, 2 * PI);
                if (d < 0) d += 2 * PI;
                if (d > 1e-9 && d < dk) dk = d;
            };
            if (r >= py) { double t = sqrt(max(0.0, r * r - py * py)); consider(px + t, 0); consider(px - t, 0); }
            if (r >= 1 - py) { double t = sqrt(max(0.0, r * r - (1 - py) * (1 - py))); consider(px + t, 1); consider(px - t, 1); }
            if (r >= px) { double t = sqrt(max(0.0, r * r - px * px)); consider(0, py + t); consider(0, py - t); }
            if (r >= 1 - px) { double t = sqrt(max(0.0, r * r - (1 - px) * (1 - px))); consider(1, py + t); consider(1, py - t); }
            if (dk < 1e17) {
                if (dk < best - 1e-7) { best = dk; landers.clear(); landers.push_back(k); }
                else if (fabs(dk - best) < 1e-7) landers.push_back(k);
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
            for (int i = 0; i < 4; i++) {
                if (fabs(c[i].x) < 5e-8) c[i].x = 0;
                if (fabs(c[i].x - 1) < 5e-8) c[i].x = 1;
                if (fabs(c[i].y) < 5e-8) c[i].y = 0;
                if (fabs(c[i].y - 1) < 5e-8) c[i].y = 1;
            }
        }
        {
            vector<double> v;
            for (int i = 0; i < 4; i++) v.push_back(c[i].x * 3.0 + c[i].y);
            sort(v.begin(), v.end());
            bool ok = true;
            for (int i = 0; i < 4; i++) if (fabs(v[i] - initSig[i]) > 1e-6) ok = false;
            if (ok) return step;
        }
        int np = -1;
        for (int k : landers) if (feasible(c, k)) { np = k; break; }
        if (np < 0) {
            double bestArc = -1;
            auto periPos = [](const Pt& p) -> double {
                if (onBottom(p)) return p.x;
                if (onRight(p)) return 1 + p.y;
                if (onTop(p)) return 2 + (1 - p.x);
                if (onLeft(p)) return 3 + (1 - p.y);
                return -1;
            };
            for (int k = 0; k < 4; k++) {
                if (!onBoundary(c[k]) || !feasible(c, k)) continue;
                double a = periPos(c[k]);
                if (a > bestArc) { bestArc = a; np = k; }
            }
        }
        if (np < 0) return -1;
        pivot = np;
    }
    return -1;
}
int main(int argc, char** argv) {
    int qmax = (argc > 1) ? atoi(argv[1]) : 30;
    int maxsteps = (argc > 2) ? atoi(argv[2]) : 120;
    for (int q = 2; q <= qmax; q++) {
        for (int p = 1; p < q; p++) {
            if (__gcd(p, q) != 1) continue;
            int s = simulate((double)p / q, maxsteps);
            if (s > 0) printf("b=%d/%d steps=%d\n", p, q, s);
        }
    }
    return 0;
}
