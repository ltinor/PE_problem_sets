// PE714 fast D(K) computer
// d(n) = 最小双字数倍数; D(K) = sum_{n<=K} d(n)
// 算法: n 从大到小; 初值上界 cap = min(d(m)) over 倍数 m=2n,3n,...<=K (n|m|值 => d(n)<=d(m));
//   对 45 个无序数字集 {d1<d2} 做 (长度,字典序) 序 BFS (FIFO, 数字升序扩展, 按余数去重),
//   首个余数 0 即该集合最小值; 深度上限 = len(best) (更长的数不可能更小).
// BFS 正确性: 同长度下前缀决定字典序 => 层内按字典序扩展 + 数字升序 => 全局 (长度,字典序) 序.
// 复杂度: 每 (n, 集合) 至少 O(min(n, 2^cap)) 状态, 用版本戳避免清空数组.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

static vector<int> stamp_, dist_, parRes_, parDig_, qbuf_;
static int curStamp_ = 0;

// 最小 {d1,d2}-数字串 (首位非0) 且被 n 整除, 长度 <= Lcap; 无则 -1
static i128 bfsPair(int n, int d1, int d2, int Lcap) {
    ++curStamp_;
    int* stamp = stamp_.data();
    int* dist = dist_.data();
    int* parRes = parRes_.data();
    int* parDig = parDig_.data();
    int* q = qbuf_.data();
    int qn = 0;

    auto visit = [&](int r, int len, int par, int dig) {
        if (stamp[r] != curStamp_) {
            stamp[r] = curStamp_; dist[r] = len; parRes[r] = par; parDig[r] = dig;
            q[qn++] = r;
            return (r == 0);
        }
        return false;
    };

    if (Lcap < 1) return -1;
    if (d1 != 0 && visit(d1 % n, 1, -1, d1)) return d1;
    if (visit(d2 % n, 1, -1, d2)) return d2;

    for (int head = 0; head < qn; head++) {
        int r = q[head];
        int len = dist[r];
        if (len >= Lcap) continue;
        int base = r * 10;
        auto build = [&]() {
            i128 v = 0;
            vector<int> ds;
            int cur2 = 0;
            while (cur2 != -1) { ds.push_back(parDig[cur2]); cur2 = parRes[cur2]; }
            for (auto it = ds.rbegin(); it != ds.rend(); it++) v = v * 10 + *it;
            return v;
        };
        if (visit((base + d1) % n, len + 1, r, d1)) return build();
        if (visit((base + d2) % n, len + 1, r, d2)) return build();
    }
    return -1;
}

static int digits10(i128 v) { int c = 0; while (v > 0) { v /= 10; c++; } return c; }

static string i128str(i128 v) {
    if (v == 0) return "0";
    string s; while (v > 0) { s += char('0' + (int)(v % 10)); v /= 10; }
    reverse(s.begin(), s.end()); return s;
}

// 返回每个 n 的 d(n) (下标 1..K)
static vector<i128> computeAll(int K) {
    stamp_.assign(K + 1, 0); dist_.assign(K + 1, 0);
    parRes_.assign(K + 1, 0); parDig_.assign(K + 1, 0);
    qbuf_.assign(K + 1, 0);
    vector<i128> dval(K + 1, -1);

    // 45 个无序数字集 d1<d2
    vector<pair<int,int>> pairs;
    for (int a = 0; a <= 8; a++) for (int b = a + 1; b <= 9; b++) pairs.push_back({a, b});

    for (int n = K; n >= 1; n--) {
        i128 best = -1;
        for (ll m = 2LL * n; m <= K; m += n)
            if (dval[m] > 0 && (best < 0 || dval[m] < best)) best = dval[m];
        int Lcap = (best < 0) ? INT_MAX : digits10(best);
        for (auto& [d1, d2] : pairs) {
            i128 v = bfsPair(n, d1, d2, Lcap);
            if (v > 0 && (best < 0 || v < best)) {
                best = v; Lcap = digits10(best);
            }
        }
        dval[n] = best;
    }
    return dval;
}

int main(int argc, char** argv) {
    int K = (argc > 1) ? atoi(argv[1]) : 50000;

    // 锚点自检: d 例题
    {
        auto dv = computeAll(400);
        auto chk = [&](int n, const char* want) {
            string got = i128str(dv[n]);
            printf("d(%d) = %s %s\n", n, got.c_str(), got == want ? "OK" : (string("FAIL want ") + want).c_str());
        };
        chk(12, "12"); chk(102, "1122"); chk(103, "515"); chk(290, "11011010"); chk(317, "211122");
        i128 s = 0; for (int i = 1; i <= 110; i++) s += dv[i];
        printf("D(110) = %s (want 11047)\n", i128str(s).c_str());
        s = 0; for (int i = 1; i <= 150; i++) s += dv[i];
        printf("D(150) = %s (want 53312)\n", i128str(s).c_str());
        s = 0; for (int i = 1; i <= 400; i++) s += dv[i];
        // D(400) 无官方值, 打印供 D(500) 差值核对
        printf("D(400) = %s\n", i128str(s).c_str());
    }

    printf("computing D(%d)...\n", K);
    auto t0 = chrono::steady_clock::now();
    auto dv = computeAll(K);
    auto t1 = chrono::steady_clock::now();
    i128 total = 0;
    for (int i = 1; i <= K; i++) {
        if (dv[i] <= 0) { printf("UN SOLVED n=%d\n", i); return 1; }
        total += dv[i];
    }
    string S = i128str(total);
    // 科学计数 13 位有效 (四舍五入)
    int exp10 = (int)S.size() - 1;
    string mant;
    for (int i = 0; i < 14 && i < (int)S.size(); i++) mant += S[i]; // 1 + 13 位用于舍入
    int roundUp = 0;
    if ((int)S.size() > 14 && S[14] >= '5') roundUp = 1;
    // 13 位 = mant[0] + mant[1..12]... 重新取: 前 13 位 + 第 14 位舍入
    string m13 = S.substr(0, 13);
    if (roundUp) {
        int i = 12;
        while (i >= 0) { if (m13[i] == '9') { m13[i] = '0'; i--; } else { m13[i]++; break; } }
        if (i < 0) { m13 = "1" + m13.substr(0, 12); exp10++; }
    }
    string sci = m13.substr(0, 1) + "." + m13.substr(1) + "e" + to_string(exp10);
    printf("time = %.1fs\n", chrono::duration<double>(t1 - t0).count());
    printf("D(%d) exact = %s\n", K, S.c_str());
    printf("D(%d) sci   = %s\n", K, sci.c_str());
    // 供 data 生成的若干中间 D(k)
    for (int k : {110, 150, 500, 1000, 5000, 10000, 20000, 50000}) {
        if (k > K) continue;
        i128 s = 0; for (int i = 1; i <= k; i++) s += dv[i];
        printf("D(%d) = %s\n", k, i128str(s).c_str());
    }
    return 0;
}
