// 4 步回归族枚举: 对 b 扫描 4 步后的 pivot 偏离, 极小值细化
using ll = long long;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <bits/stdc++.h>
using namespace std;
struct Pt { double x, y; };
int H = 4; // 步数
// 运行 H 步, 返回第 H 步后的 pivot
Pt run(double b, vector<double>& angs) {
    Pt c[4] = {{0,0},{b,0},{b,b},{0,b}};
    int pivot = 1;
    angs.clear();
    for (int step = 1; step <= H; step++) {
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
                if (d > 1e-12 && d < dk) dk = d;
            };
            if (r >= py) { double t = sqrt(max(0.0,r*r-py*py)); consider(px+t,0); consider(px-t,0); }
            if (r >= 1-py) { double t = sqrt(max(0.0,r*r-(1-py)*(1-py))); consider(px+t,1); consider(px-t,1); }
            if (r >= px) { double t = sqrt(max(0.0,r*r-px*px)); consider(0,py+t); consider(0,py-t); }
            if (r >= 1-px) { double t = sqrt(max(0.0,r*r-(1-px)*(1-px))); consider(1,py+t); consider(1,py-t); }
            if (dk < 1e17) {
                if (dk < best-1e-12) { best = dk; landers.clear(); landers.push_back(k); }
                else if (fabs(dk-best) < 1e-12) landers.push_back(k);
            }
        }
        if (landers.empty()) { angs.push_back(-1); return c[pivot]; }
        angs.push_back(best);
        double s = sin(-best), co = cos(-best);
        for (int i = 0; i < 4; i++) {
            if (i == pivot) continue;
            double dx = c[i].x-px, dy = c[i].y-py;
            c[i].x = px + dx*co - dy*s; c[i].y = py + dx*s + dy*co;
        }
        // 新 pivot: 落地者中可行者
        auto onB = [](const Pt& p) {
            auto z = [](double v){ return fabs(v) < 1e-9; };
            return z(p.y)||z(p.y-1)||z(p.x)||z(p.x-1);
        };
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
        if (np < 0) { angs.push_back(-1); return c[pivot]; }
        pivot = np;
    }
    return c[pivot];
}
int main(int argc, char** argv) {
    ll N = (argc > 1) ? atoll(argv[1]) : 200000;
    double lo = 0.5 + 1e-9, hi = 1.0 - 1e-9;
    // 扫描: 记录每点的 (pivot x 偏差, pivot y) — 回归点: y=0 且 x=b
    vector<double> bs(N+1);
    vector<Pt> piv(N+1);
    for (ll i = 0; i <= N; i++) {
        double b = lo + (hi-lo)*i/N;
        vector<double> angs;
        Pt p = run(b, angs);
        bs[i] = b; piv[i] = p;
    }
    // 找 y 接近 0 的局部极小
    for (ll i = 1; i < N; i++) {
        if (1) {
            printf("b=%.10f pivot=(%.8f,%.8f) dx=%.3e\n", bs[i], piv[i].x, piv[i].y, piv[i].x-bs[i]);
        }
    }
    return 0;
}
