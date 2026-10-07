// 933 终版工具 (v2): 闭式对全 w 成立 (含 w=2: B_2=-1 自动成立)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char** argv) {
    int W = 123, H = atoi(argv[1]);
    vector<vector<int>> g(W+1, vector<int>(H+1, 0)), C(W+1, vector<int>(H+1, 0));
    for (int w = 2; w <= W; w++)
        for (int h = 2; h <= H; h++) {
            vector<int> r(h, 0), xs; xs.reserve(256);
            long long zeros = 0;
            for (int i = 1; i < w; i++) {
                int *gi = g[i].data(), *gw = g[w-i].data();
                for (int j = 1; j < h; j++) r[j] = gi[j] ^ gw[j];
                for (int j = 1; j < h; j++) {
                    int x = r[j] ^ r[h-j];
                    xs.push_back(x);
                    if (x == 0) zeros++;
                }
            }
            C[w][h] = (int)zeros;
            sort(xs.begin(), xs.end());
            xs.erase(unique(xs.begin(), xs.end()), xs.end());
            int mex = 0; while ((size_t)mex < xs.size() && xs[mex] == mex) mex++;
            g[w][h] = mex;
        }
    vector<int> tau(W+1, 2), G(W+1, 0);
    int taumax = 0;
    for (int i = 2; i <= W; i++) {
        G[i] = g[i][H];
        for (int h = H; h >= 2; h--) if (g[i][h] != G[i]) { tau[i] = h; break; }
        if (tau[i] > taumax) taumax = tau[i];
    }
    printf("TAUMAX=%d\n", taumax);
    vector<int> Tw(W+1, 2); vector<ll> Bw(W+1, 0), pre(W+1, 0);
    int bad = 0;
    for (int w = 2; w <= W; w++) {
        ll sB = 0; int tstar = 0;
        for (int i = 1; i < w; i++) {
            int t = max(tau[i], tau[w-i]) + 1;   // t = 首个稳定位置 = 最后偏离点 + 1
            tstar = max(tstar, t);
            int z = 0;
            for (int j = 1; j < t; j++)          // 边界带含 tau* 本身
                if ((g[i][j] ^ g[w-i][j]) == (G[i] ^ G[w-i])) z++;
            sB += 1 - 2*t + 2*z;
        }
        Bw[w] = sB;
        for (ll h : { (ll)H, (ll)H - 1 }) {
            if (h >= 2*tstar - 1) {
                ll model = (ll)(w-1)*h + sB;
                if (model != C[w][h]) { bad++; if (bad <= 8) printf("MISMATCH w=%d h=%lld model=%lld actual=%d\n", w, h, model, C[w][h]); }
            }
        }
        int T = 2;
        for (int h = H; h >= 3; h--) if (C[w][h] - C[w][h-1] != w-1) { T = h; break; }
        Tw[w] = T;
        for (int h = 2; h <= min(T, H); h++) pre[w] += C[w][h];
    }
    printf("closed-form bad=%d\n", bad);
    auto model = [&](int WW, ll HH) {
        ll s = 0;
        for (int w = 2; w <= WW; w++) {
            if (HH <= H) { for (int h = 2; h <= (int)HH; h++) s += C[w][h]; continue; }
            s += pre[w];
            ll l1 = Tw[w] + 1;
            if (l1 <= HH) {
                ll l2 = HH, cnt = l2 - l1 + 1;
                s += (ll)(w-1) * ((l1 + l2) * cnt / 2) + Bw[w] * cnt;
            }
        }
        return s;
    };
    printf("MODEL D(12,123)   = %lld (want 327398)\n", model(12, 123));
    { ll direct = 0; for (int w = 2; w <= W; w++) for (int h = 2; h <= H; h++) direct += C[w][h];
      printf("MODEL D(123,%d) = %lld\n", H, model(W, H));
      printf("DIRECT D(123,%d) = %lld\n", H, direct); }
    printf("MODEL D(123,1234567) = %lld (official 5707485980743099)\n", model(W, 1234567));
    FILE* ft = fopen("table933.txt", "w");
    fprintf(ft, "%d\n", W);
    for (int w = 2; w <= W; w++) fprintf(ft, "%d %lld %lld %lld\n", w, (ll)Tw[w], Bw[w], pre[w]);
    fclose(ft);
    return 0;
}
