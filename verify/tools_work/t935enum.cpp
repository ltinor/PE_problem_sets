// 935 分岔枚举器: 扫描 b, 检测 8 步终点枢轴的跳变 (模式分岔), 二分定位回归 b
using ll = long long;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <bits/stdc++.h>
using namespace std;
struct Pt { double x, y; };
static int FEAS_OK; // 每次运行的可行性状态: 1=正常, 0=楔死
static Pt run(double b, int steps, vector<double>* angsout = nullptr) {
    FEAS_OK = 1;
    Pt c[4] = {{0,0},{b,0},{b,b},{0,b}};
    int pivot = 1;
    for (int step = 1; step <= steps; step++) {
        double px = c[pivot].x, py = c[pivot].y;
        double best = 1e18; vector<int> landers;
        for (int k = 0; k < 4; k++) {
            if (k == pivot) continue;
            double dx = c[k].x-px, dy = c[k].y-py;
            double r = sqrt(dx*dx+dy*dy), th0 = atan2(dy,dx);
            double dk = 1e18;
            auto consider = [&](double qx, double qy) {
                if (qx < -1e-12 || qx > 1+1e-12 || qy < -1e-12 || qy > 1+1e-12) return;
                double th = atan2(qy-py, qx-px);
                double d = fmod(th0-th, 2*M_PI); if (d < 0) d += 2*M_PI;
                if (d > 1e-13 && d < dk) dk = d;
            };
            auto addEdge = [&](int which) {
                if (which == 0 && r >= py) { double t = sqrt(max(0.0,r*r-py*py)); consider(px+t,0); consider(px-t,0); }
                if (which == 1 && r >= 1-py) { double t = sqrt(max(0.0,r*r-(1-py)*(1-py))); consider(px+t,1); consider(px-t,1); }
                if (which == 2 && r >= px) { double t = sqrt(max(0.0,r*r-px*px)); consider(0,py+t); consider(0,py-t); }
                if (which == 3 && r >= 1-px) { double t = sqrt(max(0.0,r*r-(1-px)*(1-px))); consider(1,py+t); consider(1,py-t); }
            };
            for (int e2 = 0; e2 < 4; e2++) addEdge(e2);
            if (dk < 1e17) {
                if (dk < best-1e-13) { best = dk; landers.clear(); landers.push_back(k); }
                else if (fabs(dk-best) < 1e-13) landers.push_back(k);
            }
        }
        if (landers.empty()) { FEAS_OK = 0; return c[pivot]; }
        {
            double s = sin(-best), co = cos(-best);
            for (int i = 0; i < 4; i++) {
                if (i == pivot) continue;
                double dx = c[i].x-px, dy = c[i].y-py;
                c[i].x = px + dx*co - dy*s; c[i].y = py + dx*s + dy*co;
            }
        }
        auto onB = [](const Pt& p) { auto z = [](double v){ return fabs(v) < 1e-9; }; return z(p.y)||z(p.y-1)||z(p.x)||z(p.x-1); };
        auto feas = [&](int pv) {
            for (int j = 0; j < 4; j++) {
                if (j == pv || !onB(c[j])) continue;
                double dx = c[j].x-c[pv].x, dy = c[j].y-c[pv].y;
                double vx = dy, vy = -dx;
                auto ck = [&](double nx, double ny){ return !(vx*nx+vy*ny > 1e-12); };
                if (fabs(c[j].y)<1e-9 && !ck(0,-1)) return false;
                if (fabs(c[j].y-1)<1e-9 && !ck(0,1)) return false;
                if (fabs(c[j].x)<1e-9 && !ck(-1,0)) return false;
                if (fabs(c[j].x-1)<1e-9 && !ck(1,0)) return false;
            }
            return true;
        };
        int np = -1;
        for (int k : landers) if (feas(k)) { np = k; break; }
        if (np < 0) {
            double ba = -1;
            auto peri = [](const Pt& p) { if (fabs(p.y)<1e-9) return p.x; if (fabs(p.x-1)<1e-9) return 1.0+p.y; if (fabs(p.y-1)<1e-9) return 2.0+(1-p.x); if (fabs(p.x)<1e-9) return 3.0+(1-p.y); return -1.0; };
            for (int k = 0; k < 4; k++) {
                if (!onB(c[k]) || !feas(k)) continue;
                double a = peri(c[k]); if (a > ba) { ba = a; np = k; }
            }
        }
        if (np < 0) { FEAS_OK = 0; return c[pivot]; }
        pivot = np;
    }
    return c[pivot];
}
int main(int argc, char** argv) {
    ll N = (argc > 1) ? atoll(argv[1]) : 200000;
    double lo = 0.0001001, hi = 0.9999999;
    vector<double> bs(N+1); vector<Pt> pv(N+1);
    vector<int> feas(N+1);
    for (ll i = 0; i <= N; i++) {
        double b = lo + (hi-lo)*i/N;
        bs[i] = b;
        pv[i] = run(b, 100);
        feas[i] = FEAS_OK;
    }
    // 检测跳变: 相邻点 8 步终点枢轴距离 > 0.05 (排除楔死点: 两端 feas 或 单端)
    ll nb = 0;
    for (ll i = 1; i <= N; i++) {
        double ddx = hypot(pv[i].x-pv[i-1].x, pv[i].y-pv[i-1].y);
        if (ddx > 0.05 && feas[i-1] && feas[i]) {
            // 二分
            double bl = bs[i-1], br = bs[i];
            for (int it = 0; it < 55; it++) {
                double bm = (bl + br) / 2;
                Pt pm = run(bm, 100);
                double dd = hypot(pm.x-pv[i-1].x, pm.y-pv[i-1].y);
                // 与左端比较: 若仍接近左端 -> bm 在左侧
                if (dd < 0.05 && FEAS_OK) bl = bm; else br = bm;
            }
            double bm = (bl + br) / 2;
            Pt pL = run(bl - 1e-9, 100); Pt pR = run(br + 1e-9, 100);
            (void)pL; (void)pR;
            printf("bifurcation b=%.13f  (L pivot %.6f %.6f / R pivot %.6f %.6f)\n", bm, pv[i-1].x, pv[i-1].y, pv[i].x, pv[i].y);
            nb++;
        }
    }
    printf("total bifurcations=%lld\n", nb);
    return 0;
}
