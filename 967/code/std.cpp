#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 967 简单版: B-Trivisible Numbers / B-三除数
//
// 给定 N, B, 求 F(N,B) = 不超过 N 的 B-三除数个数。
// n 是 B-三除数当且仅当 n 的所有不大于 B 的不同质因数之和能被 3 整除。
//
// 算法: 容斥 (莫比乌斯反演) + 子集枚举。
// 记小质数集合 P = {p ≤ B}。对每个 n, 记 D(n) = {p ∈ P : p | n}。
// 令 f(S) = #{n ≤ N : D(n) = S} (恰有 S 这组小质因子),
//    g(T) = #{n ≤ N : T ⊆ D(n)} = ⌊N / ∏_{p∈T} p⌋。
// 由莫比乌斯反演 f(S) = Σ_{T⊇S} (-1)^{|T|-|S|} g(T), 于是
//   F = Σ_{S: sum(S)≡0 mod 3} f(S)
//     = Σ_T (-1)^{|T|} g(T) · h(T),
// 其中 h(T) = Σ_{S⊆T, sum(S)≡0 mod 3} (-1)^{|S|} 恰为生成多项式
// ∏_{p∈T}(1 - x^{p mod 3}) 中 x 指数 ≡ 0 (mod 3) 的系数和, 可用长度 3 的系数数组递推。
// 枚举所有子集 T, 复杂度 O(2^{π(B)})。B ≤ 40 时 π(B) ≤ 12, 完全可行。

vector<int> primes_up_to(int B) {
    vector<int> ps;
    for (int i = 2; i <= B; i++) {
        bool ok = true;
        for (int p : ps) {
            if (p * p > i) break;
            if (i % p == 0) { ok = false; break; }
        }
        if (ok) ps.push_back(i);
    }
    return ps;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; int B;
    cin >> N >> B;

    vector<int> ps = primes_up_to(B);
    int k = (int)ps.size();
    i128 ans = 0;

    // 递归枚举子集 T (idx 表示下一个可选的质数下标)。
    // prod = ∏_{p∈T} p, sign = (-1)^|T|, c[0..2] = ∏_{p∈T}(1 - x^{p%3}) 的系数。
    function<void(int, ll, ll, ll, ll, ll)> dfs =
        [&](int idx, ll prod, ll sign, ll c0, ll c1, ll c2) {
            ans += sign * (i128)(N / prod) * c0;   // 当前子集 T 的贡献
            for (int j = idx; j < k; j++) {
                ll p = ps[j];
                if (prod > N / p) break;            // 之后质数更大, 乘积只会更大
                int r = p % 3;
                ll old[3] = {c0, c1, c2};
                // 乘 (1 - x^r): new[j] = old[j] - old[(j-r) mod 3]
                ll n0 = old[0] - old[(0 - r + 3) % 3];
                ll n1 = old[1] - old[(1 - r + 3) % 3];
                ll n2 = old[2] - old[(2 - r + 3) % 3];
                dfs(j + 1, prod * p, -sign, n0, n1, n2);
            }
        };

    dfs(0, 1, 1, 1, 0, 0);

    cout << (ll)ans << "\n";
    return 0;
}
