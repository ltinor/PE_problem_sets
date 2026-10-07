// 批量验证分岔候选: 每个 b 跑精确模拟得首回归步数, 聚合 F(N)
using ll = long long;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <bits/stdc++.h>
using namespace std;
struct Pt { double x, y; };
static double SNAPQ = 0;
struct Pt2 { double x, y; };
int main(int argc, char** argv) {
    // 从 stdin 读候选 b; 参数: maxsteps
    ll maxsteps = (argc > 1) ? atoll(argv[1]) : 3000;
    vector<double> cands;
    double b;
    while (cin >> b) cands.push_back(b);
    // 逐个验证 (复用 fp 模拟)
    // ... 与 t935_scan3 的 simulate 相同但无吸附
    vector<ll> rets;
    ll verified = 0;
    for (double bb : cands) {
        double B = bb;
        Pt c[4] = {{0,0},{B,0},{B,B},{0,B}};
        int pivot = 1;
        vector<double> sig;
        for (int i = 0; i < 4; i++) sig.push_back(c[i].x * 3.0 + c[i].y);
        sort(sig.begin(), sig.end());
        ll ret = -1;
        auto onB = [](const Pt2& p) { return false; }; // placeholder
        for (ll step = 1; step <= maxsteps && ret < 0; step++) {
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
                auto addE = [&](int e2) {
                    if (e2 == 0 && r >= py) { double t = sqrt(max(0.0,r*r-py*py)); consider(px+t,0); consider(px-t,0); }
                    if (e2 == 1 && r >= 1-py) { double t = sqrt(max(0.0,r*r-(1-py)*(1-py))); consider(px+t,1); consider(px-t,1); }
                    if (e2 == 2 && r >= px) { double t = sqrt(max(0.0,r*r-px*px)); consider(0,py+t); consider(0,py-t); }
                    if (e2 == 3 && r >= 1-px) { double t = sqrt(max(0.0,r*r-(1-px)*(1-px))); consider(1,py+t); consider(1,py-t); }
                };
                for (int e2 = 0; e2 < 4; e2++) addE(e2);
                if (dk < 1e17) {
                    if (dk < best-1e-13) { best = dk; landers.clear(); landers.push_back(k); }
                    else if (fabs(dk-best) < 1e-13) landers.push_back(k);
                }
            }
            if (landers.empty()) break;
            {
                double s = sin(-best), co = cos(-best);
                for (int i = 0; i < 4; i++) {
                    if (i == pivot) continue;
                    double dx = c[i].x-px, dy = c[i].y-py;
                    c[i].x = px + dx*co - dy*s; c[i].y = py + dx*s + dy*co;
                }
            }
            {
                vector<double> v;
                for (int i = 0; i < 4; i++) v.push_back(c[i].x * 3.0 + c[i].y);
                sort(v.begin(), v.end());
                bool ok = true;
                for (int i = 0; i < 4; i++) if (fabs(v[i] - sig[i]) > 1e-7) ok = false;
                if (ok) { ret = step; break; }
            }
            int np = -1;
            auto onBd = [](const Pt& p) { auto z = [](double v){ return fabs(v) < 1e-9; }; return z(p.y)||z(p.y-1)||z(p.x)||z(p.x-1); };
            auto feas2 = [&](int pv) {
                for (int j = 0; j < 4; j++) {
                    if (j == pv || !onBd(c[j])) continue;
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
            for (int k : landers) if (feas2(k)) { np = k; break; }
            if (np < 0) {
                double ba = -1;
                auto peri = [](const Pt& p) { if (fabs(p.y)<1e-9) return p.x; if (fabs(p.x-1)<1e-9) return 1.0+p.y; if (fabs(p.y-1)<1e-9) return 2.0+(1-p.x); if (fabs(p.x)<1e-9) return 3.0+(1-p.y); return -1.0; };
                for (int k = 0; k < 4; k++) {
                    if (!onBd(c[k]) || !feas2(k)) continue;
                    double a = peri(c[k]); if (a > ba) { ba = a; np = k; }
                }
            }
            if (np < 0) break;
            pivot = np;
        }
        rets.push_back(ret);
        if (ret > 0) verified++;
    }
    printf("candidates=%zu verified=%lld\n", cands.size(), verified);
    // F(N) 聚合
    map<ll, ll> cnt;
    for (ll r : rets) if (r > 0) cnt[r]++;
    ll cum = 0;
    vector<pair<ll,ll>> pts;
    for (auto& [k, v] : cnt) { cum += v; pts.push_back({k, cum}); }
    for (ll N : {6LL, 10LL, 20LL, 50LL, 100LL, 200LL, 500LL, 1000LL, 2000LL}) {
        ll f = 0;
        for (auto& [k, v] : pts) if (k <= N) f = v;
        printf("F(%lld) = %lld\n", N, f);
    }
    // 输出每个候选的步数
    FILE* f = fopen("verified935.txt", "w");
    for (size_t i = 0; i < cands.size(); i++)
        fprintf(f, "%.15f %lld\n", cands[i], rets[i]);
    fclose(f);
    return 0;
}
