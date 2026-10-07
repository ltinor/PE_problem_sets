// 689 实验 v2: 归一化量化 + 深度预算
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int DEPTH = 250;
ll QUANT = 200000; // t/tail_k 归一化到 QUANT 个桶
unordered_map<unsigned __int128, ld> memo;

ld solve(int k, ld t, ld tk_upper, int depth) {
    if (t <= 0) return 1.0L;
    if (t >= tk_upper) return 0.0L;
    if (depth >= DEPTH) return 0.0L;
    ll q = (ll)((long double)(t / tk_upper) * QUANT);
    unsigned __int128 key = (((unsigned __int128)k) << 40) | (unsigned __int128)(unsigned ll)q;
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    ld bit = 1.0L / ((ld)k * k);
    ld tkn = 1.0L / (k);        // 下一层上界 1/(k+1-0.5)
    ld r = 0.5L * solve(k + 1, t, tkn, depth + 1)
         + 0.5L * solve(k + 1, t - bit, tkn, depth + 1);
    memo[key] = r;
    return r;
}

int main(int argc, char** argv) {
    if (argc > 1) QUANT = atoll(argv[1]);
    if (argc > 2) DEPTH = atoi(argv[2]);
    ld p_rest = solve(2, 0.5L, 1.0L/1.5L, 0);
    ld ans = 0.5L + 0.5L * p_rest;
    cerr << "memo=" << memo.size() << endl;
    cout << fixed << setprecision(10) << (double)ans << endl;
}
