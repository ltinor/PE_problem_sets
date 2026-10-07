// 933 后处理: 读 g/c 表, 按 C(w,h) = sum_i [(h - 2t* + 1) + 2 z_i(w)] 闭式建模
// t*(w) = max(tau_i, tau_{w-i}); z_i(w) = #{j in [1, t*-1]: g(i,j)^g(w-i,j) == G(i)^G(w-i)}
// 验证: 全 w 的 C(w,6000)/C(w,5800) 模型 vs 实际; D(12,123)=327398; 最终 D(123,1234567)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char** argv) {
    int W = 123, H = atoi(argv[1]);   // H = 表的列数-1
    vector<vector<int>> g(W+1, vector<int>(H+1)), C(W+1, vector<int>(H+1));
    {
        FILE* f = fopen("g933.bin", "rb");
        for (int i = 1; i <= W; i++) fread(g[i].data(), sizeof(int), H+1, f);
        fclose(f);
        f = fopen("c933.bin", "rb");
        for (int i = 1; i <= W; i++) fread(C[i].data(), sizeof(int), H+1, f);
        fclose(f);
    }
    // tau_i 与 G(i)
    vector<int> tau(W+1, 2), G(W+1, 0);
    int taumax = 0;
    for (int i = 2; i <= W; i++) {
        G[i] = g[i][H];
        tau[i] = 2;
        for (int h = H; h >= 2; h--) if (g[i][h] != G[i]) { tau[i] = h; break; }
        if (tau[i] > taumax) taumax = tau[i];
    }
    printf("taumax=%d\n", taumax);
    // z_i(w) 对所有 w: ztab[w][i] = #{j in [1, t*-1]: g(i,j)^g(w-i,j) == G(i)^G(w-i)}
    // t* = max(tau_i, tau_{w-i}); 范围 j <= t*-1 <= taumax-1
    vector<vector<int>> ztab(W+1, vector<int>(W+1, 0));
    for (int w = 3; w <= W; w++)
        for (int i = 1; i < w; i++) {
            int t = max(tau[i], tau[w-i]);
            if (t < 2) { ztab[w][i] = 0; continue; }
            int cnt = 0;
            for (int j = 1; j < t; j++)
                if ((g[i][j] ^ g[w-i][j]) == (G[i] ^ G[w-i])) cnt++;
            ztab[w][i] = cnt;
        }
    // 闭式: C(w,h) = sum_i [(h - 2t* + 1) + 2 z_i(w)],  要求 h >= 2t*-1
    // B'_w = sum_i [1 - 2t* + 2 z_i(w)];  slope = w-1
    // 验证 1: C(w, 6000) 与 C(w, 6000-1) 模型 vs 实际 (全 w)
    int bad = 0;
    for (int w = 3; w <= W; w++) {
        ll sB = 0;
        for (int i = 1; i < w; i++) {
            int t = max(tau[i], tau[w-i]);
            sB += 1 - 2*t + 2*ztab[w][i];
        }
        for (int h : {H, H-1, H-2}) {
            if (h < 2*taumax - 1) continue;
            ll model = (ll)(w-1)*h + sB;
            if (model != C[w][h]) {
                if (bad < 10) printf("MISMATCH w=%d h=%d model=%lld actual=%d\n", w, h, model, C[w][h]);
                bad++;
            }
        }
    }
    printf("closed-form mismatches (h>=2taumax-1): %d\n", bad);
    // 验证 2: D(12,123) — w<=12 用直接表 (h<=123 <= H)
    ll D = 0;
    for (int w = 2; w <= 12; w++) for (int h = 2; h <= 123; h++) D += C[w][h];
    printf("D(12,123) = %lld (want 327398)\n", D);
    // 最终: D(W, HBIG): w 的 h<=H 部分用表直和, h in (H, HBIG] 用闭式 (斜率 w-1, 截距 B'_w)
    ll HBIG = 1234567;
    ll Dpe = 0;
    for (int w = 2; w <= W; w++) {
        for (int h = 2; h <= H; h++) Dpe += C[w][h];
        ll sB = 0;
        for (int i = 1; i < w; i++) {
            int t = max(tau[i], tau[w-i]);
            sB += 1 - 2*t + 2*ztab[w][i];
        }
        // h from H+1 to HBIG: (w-1)*h + sB
        ll lo = H + 1;
        if (lo <= HBIG) {
            ll cnt = HBIG - lo + 1;
            Dpe += (ll)(w-1) * ((lo + HBIG) * cnt / 2) + sB * cnt;
        }
    }
    printf("MODEL D(123,1234567) = %lld (official 5707485980743099)\n", Dpe);
    // 顺带: 生成 std 用表 (w, slope=w-1, B'_w) 供嵌入
    FILE* ft = fopen("table933.txt", "w");
    for (int w = 2; w <= W; w++) {
        ll sB = 0;
        for (int i = 1; i < w; i++) {
            int t = max(tau[i], tau[w-i]);
            sB += 1 - 2*t + 2*ztab[w][i];
        }
        fprintf(ft, "%d %lld\n", w, sB);
    }
    fclose(ft);
    return 0;
}
