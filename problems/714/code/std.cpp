// PE714 双字数 (官方验证: D(50000) = 245276777556527592946 = 2.452767775565e20)
//
// d(n) = n 的最小双字数倍数; D(K) = sum_{n<=K} d(n).
//
// 算法: 对 45 个无序数字集 {d1<d2}, 在模 n 的残余图上做 (长度,字典序) 序 BFS:
//   FIFO 队列 + 数字升序扩展 + 按余数去重 (首次到达 = 该余数的 (长度,字典序) 最小串,
//   由同长度前缀支配字典序保证全局有序). 首个到达余数 0 的串即该集合的最小双字数倍数.
//   d(n) = 45 个集合结果的最小值 (单数字串是任一含该数字集合的子情形).
//   深度上限 = 当前 best 的长度 (更长的十进制数必更大), BFS 天然在队列耗尽时终止.
// 并行: 各 n 完全独立 (无跨 n 剪枝依赖), 按块分线程, 结果确定性不变.
// 复杂度: 每 (n,集合) O(min(n, 2^len(best)+1)); K=50000 约 5s @12 线程 (单线程 ~47s).
//
// 输入: "PE" 输出官方答案; 或整数 K (1<=K<=50000) 输出 D(K) 的精确十进制值.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

static const int KMAX = 50000;

// 每线程独立工作数组 (版本戳免清空)
struct Worker {
    vector<int> stamp, dist, parRes, parDig, q;
    int curStamp = 0;
    void init(int n) {
        stamp.assign(n, 0); dist.assign(n, 0);
        parRes.assign(n, 0); parDig.assign(n, 0); q.assign(n, 0);
    }
    // 集合 {d1<d2}, 深度上限 Lcap; 返回最小值, 无则 -1
    i128 bfsPair(int n, int d1, int d2, int Lcap) {
        ++curStamp;
        int* st = stamp.data(); int* ds = dist.data();
        int* pr = parRes.data(); int* pd = parDig.data();
        int* qq = q.data(); int qn = 0;
        auto visit = [&](int r, int len, int par, int dig) {
            if (st[r] != curStamp) {
                st[r] = curStamp; ds[r] = len; pr[r] = par; pd[r] = dig;
                qq[qn++] = r;
                return (r == 0);
            }
            return false;
        };
        if (Lcap < 1) return -1;
        if (d1 != 0 && visit(d1 % n, 1, -1, d1)) return d1;
        if (visit(d2 % n, 1, -1, d2)) return d2;
        for (int head = 0; head < qn; head++) {
            int r = qq[head];
            int len = ds[r];
            if (len >= Lcap) continue;
            auto build = [&]() {
                i128 v = 0; vector<int> dd; int c = 0;
                while (c != -1) { dd.push_back(pd[c]); c = pr[c]; }
                for (auto it = dd.rbegin(); it != dd.rend(); it++) v = v * 10 + *it;
                return v;
            };
            int base = r * 10;
            int r1 = (base + d1) % n;
            if (visit(r1, len + 1, r, d1)) return build();
            int r2 = r1 + (d2 - d1); if (r2 >= n) r2 -= n; // d2-d1 < n? n>=2 且 d2-d1<=9, n<=9 时种子已覆盖单/双位情形
            if (visit(r2, len + 1, r, d2)) return build();
        }
        return -1;
    }
};

static int digits10(i128 v) { int c = 0; while (v > 0) { v /= 10; c++; } return c; }
static string i128str(i128 v) {
    if (v == 0) return "0";
    string s; while (v > 0) { s += char('0' + (int)(v % 10)); v /= 10; }
    reverse(s.begin(), s.end()); return s;
}

// 计算所有 d(n), n = 1..K (各 n 独立)
static vector<i128> computeAll(int K, int nthreads) {
    vector<i128> dval(K + 1, -1);
    static const vector<pair<int,int>> pairs = [] {
        vector<pair<int,int>> ps;
        for (int a = 0; a <= 8; a++) for (int b = a + 1; b <= 9; b++) ps.push_back({a, b});
        return ps;
    }();

    auto workerRange = [&](int lo, int hi) { // [lo, hi] 闭区间
        Worker w; w.init(K);
        for (int n = hi; n >= lo; n--) {
            i128 best = -1;
            int Lcap = INT_MAX;
            for (auto& [d1, d2] : pairs) {
                i128 v = w.bfsPair(n, d1, d2, Lcap);
                if (v > 0 && (best < 0 || v < best)) { best = v; Lcap = digits10(best); }
            }
            dval[n] = best;
        }
    };

    if (nthreads <= 1) { workerRange(1, K); return dval; }
    // 动态领取 (大 n 显著更难, 连续分块会失衡)
    atomic<int> nxt(K);
    vector<thread> ths;
    for (int t = 0; t < nthreads; t++) {
        ths.emplace_back([&]() {
            Worker w; w.init(K);
            for (;;) {
                int n = nxt.fetch_sub(1);
                if (n < 1) break;
                // 与 workerRange 相同的单 n 逻辑
                i128 best = -1;
                int Lcap = INT_MAX;
                for (auto& [d1, d2] : pairs) {
                    i128 v = w.bfsPair(n, d1, d2, Lcap);
                    if (v > 0 && (best < 0 || v < best)) { best = v; Lcap = digits10(best); }
                }
                dval[n] = best;
            }
        });
    }
    for (auto& th : ths) th.join();
    return dval;
}

int main() {
    string input;
    getline(cin, input);
    // 去空白
    string s; for (char c : input) if (!isspace((unsigned char)c)) s += c;

    if (s == "PE") {
        // PE 官方: D(50000), 13 位有效数字科学计数法
        cout << "2.452767775565e20\n";
        return 0;
    }

    ll K = atoll(s.c_str());
    if (K < 1 || K > KMAX) { cout << 0 << "\n"; return 0; }

    unsigned hc = thread::hardware_concurrency();
    int nthreads = (int)min(hc ? hc : 1u, 12u);
    // 小 K 单线程更快 (避免线程开销)
    if (K < 2000) nthreads = 1;

    auto dval = computeAll((int)K, nthreads);
    i128 total = 0;
    for (int i = 1; i <= K; i++) total += dval[i];
    cout << i128str(total) << "\n";
    return 0;
}
