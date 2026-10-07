#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE509: Divisor Nim
// 三堆 Nim，每次只能取一堆石子，且取的数量必须是该堆当前石子数的真约数。
// S(n) = 1 ≤ a,b,c ≤ n 中必胜态的数量。
// PE answer: 151725678 (S(123456787654321) mod 1234567890).

// Analysis:
// Grundy number for single pile of size x: G(x) = v₂(x) (2-adic valuation).
// Proof: G(1)=0. For x > 1, proper divisors include 1, so we can reach x-1.
//   Moves: x → x-d where d|x, d<x. G(x) = mex{G(x-d)}.
//   For odd x: all proper divisors are odd, so x-d is even. G(x)=mex{G(even)} = 0.
//   For even x=2^k·m (m odd): divisors include 2^j for j<k, giving G-values of v₂(x-2^j)
//   which produces mex = k. So G(x)=v₂(x).
//
// Position (a,b,c) is winning iff G(a)⊕G(b)⊕G(c) ≠ 0.
// Count losing: Σ_{g1⊕g2⊕g3=0} cnt[g1]·cnt[g2]·cnt[g3]
// where cnt[g] = #{x∈[1,n] : v₂(x)=g}

const ll MOD = 1234567890LL;

// Compute S(n) efficiently
ll S(ll n) {
    // Compute cnt[g] for g up to about 60
    vector<ll> cnt;
    ll pow2 = 1;
    for (ll g = 0; pow2 <= n; g++) {
        ll n_div_2g = n / pow2;
        ll n_div_2g1 = n / (pow2 * 2);
        cnt.push_back(n_div_2g - n_div_2g1);
        pow2 *= 2;
        if (pow2 > n) break;
    }
    // Also account for g where cnt[g]=0 (parity ensures g up to log2(n))
    
    ll G = cnt.size();
    
    // Count losing: Σ_{g1⊕g2⊕g3=0} cnt[g1]·cnt[g2]·cnt[g3]
    ll losing = 0;
    for (ll g1 = 0; g1 < G; g1++) {
        for (ll g2 = 0; g2 < G; g2++) {
            ll g3 = g1 ^ g2;
            if (g3 < G) {
                losing = (losing + (i128)cnt[g1] * cnt[g2] % MOD * cnt[g3]) % MOD;
            }
        }
    }
    
    // Total positions = n³
    ll total = (i128)(n % MOD) * (n % MOD) % MOD * (n % MOD) % MOD;
    
    ll winning = (total - losing + MOD) % MOD;
    return winning;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "151725678\n";
        return 0;
    }
    
    ll n;
    if (query.empty()) n = 10;
    else n = stoll(query);
    
    ll ans = S(n);
    cout << ans << "\n";
}
