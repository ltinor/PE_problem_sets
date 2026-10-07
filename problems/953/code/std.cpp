#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 953 简化版（缩数据版）：因数分解取石子游戏 (Factorisation Nim)
//
// 原题：S(N) = 1<=n<=N 中先手必败的 n 之和，求 S(1e14) mod 1e9+7。
// 简化：读入缩小后的 N，直接输出 S(N)。
//
// 游戏分析（标准 Nim / Bouton 定理）：
//   初始局面由 n 的质因数（含重数）决定，每个质因数对应一堆石子。
//   先手必败 iff 所有堆大小的异或（nim-sum）为 0。
//   设 n = prod p_i^{e_i}，堆为每个 p_i 重复 e_i 次，其异或 =
//       xor_i (e_i 为奇数 ? p_i : 0)
//   即 nim(n) = n 的"奇数次质因子"的异或（等价于 n 平方自由部分中互异质因子的异或）。
//
// 验证点：
//   n = 1：空积，异或 0，先手必败。
//   n = 70 = 2*5*7：2 xor 5 xor 7 = 0，先手必败。
//   S(10) = 1+4+9 = 14，S(100) = 455。
//
// 算法：最小质因子筛 (SPF) + 逐 n 分解，总复杂度 O(N log N)。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    if (!(cin >> N)) return 0;

    // 最小质因子筛（SPF）
    vector<int> spf(N + 1);
    for (int i = 2; i <= N; i++) spf[i] = i;
    for (ll i = 2; i * i <= N; i++) {
        if (spf[i] == i) {               // i 是质数
            for (ll j = i * i; j <= N; j += i)
                if (spf[j] == j) spf[j] = (int)i;
        }
    }

    ll ans = 0;
    for (ll n = 1; n <= N; n++) {
        ll x = n;
        ll nim = 0;
        while (x > 1) {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0) { x /= p; cnt++; }
            if (cnt & 1) nim ^= p;
        }
        if (nim == 0) ans += n;
    }

    cout << ans << "\n";
    return 0;
}
