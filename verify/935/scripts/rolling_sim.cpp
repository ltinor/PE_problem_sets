// PE935 rolling square simulator v2 (test tool)
// 规则(与原题图一致, 已对 b=1/2(4步) 与 b=2-sqrt2(4步) 手工验证):
//   - 每步绕枢轴(小正方形位于大正方形边界上的接触角)顺时针旋转, 至某个非枢轴角首次触边.
//   - 同时落地(δ 相同)取多个候选; 新枢轴 = "顺时针旋转能留在内部"的可行候选
//     (速度 v=(dy,-dx), 对每个触边角检查 v·外法线 <= tol); 优先刚落地的角.
// 用法: t935_sim <b> [maxsteps]
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

// 可行性: 以 pv 为枢轴 CW 旋转时, 所有触边的非枢轴角向内/切向移动
static bool feasible(Pt* c, int pv) {
    for (int j = 0; j < 4; j++) {
        if (j == pv || !onBoundary(c[j])) continue;
        double dx = c[j].x - c[pv].x, dy = c[j].y - c[pv].y;
        double vx = dy, vy = -dx; // CW 速度
        auto check = [&](double nx, double ny) {
            if (vx * nx + vy * ny > 1e-6) return false; // 向外 => 不可行 (容差覆盖 fp 残差)
            return true;
        };
        if (onBottom(c[j]) && !check(0, -1)) return false;
        if (onTop(c[j]) && !check(0, 1)) return false;
        if (onLeft(c[j]) && !check(-1, 0)) return false;
        if (onRight(c[j]) && !check(1, 0)) return false;
    }
    return true;
}

int main(int argc, char** argv) {
    double b = atof(argv[1]);
    int maxsteps = (argc > 2) ? atoi(argv[2]) : 200;

    Pt c[4] = {{0, 0}, {b, 0}, {b, b}, {0, b}};
    int pivot = 1; // 第一步绕底边接触角 (b,0)

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
        if (landers.empty()) { printf("step %d: no contact\n", step); return 1; }
        if (getenv("T935TRACE")) {
            fprintf(stderr, "step %2d: pivot(%9.6f,%9.6f) rot=%10.6f deg  land:", step, px, py, best * 180 / PI);
            for (int k : landers) fprintf(stderr, " (%9.6f,%9.6f)", c[k].x, c[k].y);
            fprintf(stderr, "\n");
        }

        // 旋转 (并吸附到边界线, 控制浮点漂移)
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

        // 回归检测 (角坐标集合) — 在选新枢轴之前
        {
            vector<double> v;
            for (int i = 0; i < 4; i++) v.push_back(c[i].x * 3.0 + c[i].y);
            sort(v.begin(), v.end());
            bool ok = true;
            for (int i = 0; i < 4; i++) if (fabs(v[i] - initSig[i]) > 1e-6) ok = false;
            if (ok) {
                printf("b=%.10g: FIRST RETURN after %d steps\n", b, step);
                return 0;
            }
        }

        // 新枢轴: 落地角中可行者; 否则其他触边可行角 (取沿 CW 弧长最远)
        auto periPos = [](const Pt& p) -> double {
            if (onBottom(p)) return p.x;
            if (onRight(p)) return 1 + p.y;
            if (onTop(p)) return 2 + (1 - p.x);
            if (onLeft(p)) return 3 + (1 - p.y);
            return -1;
        };
        int np = -1;
        for (int k : landers) if (feasible(c, k)) { np = k; break; }
        if (np < 0) {
            double bestArc = -1;
            for (int k = 0; k < 4; k++) {
                if (!onBoundary(c[k])) continue;
                if (!feasible(c, k)) continue;
                double a = periPos(c[k]);
                if (a > bestArc) { bestArc = a; np = k; }
            }
        }
        if (np < 0) {
            if (getenv("T935TRACE")) {
                fprintf(stderr, "  FAILDBG: corners:");
                for (int k = 0; k < 4; k++) fprintf(stderr, " (%.8f,%.8f)[b%d r%d l%d t%d f%d]", c[k].x, c[k].y, onBottom(c[k]), onRight(c[k]), onLeft(c[k]), onTop(c[k]), feasible(c, k));
                fprintf(stderr, "  landers:");
                for (int k : landers) fprintf(stderr, " (%.8f,%.8f)", c[k].x, c[k].y);
                fprintf(stderr, "\n");
            }
            printf("step %d: no feasible pivot\n", step); return 1;
        }

        // 回归检测 (角坐标集合)
        {
            vector<double> v;
            for (int i = 0; i < 4; i++) v.push_back(c[i].x * 3.0 + c[i].y);
            sort(v.begin(), v.end());
            bool ok = true;
            for (int i = 0; i < 4; i++) if (fabs(v[i] - initSig[i]) > 1e-6) ok = false;
            if (ok) {
                printf("b=%.10g: FIRST RETURN after %d steps\n", b, step);
                return 0;
            }
        }
        pivot = np;
    }
    printf("b=%.10g: no return within %d steps\n", b, maxsteps);
    return 2;
}
