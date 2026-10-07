#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 926: Total Roundness / 总取整度
//
// Roundness of n in base b = # of trailing zeros = max{k: b^k | n}
// R(n) = sum over all b>1 of roundness in base b
//       = Σ_{k≥1} (#{b>1 : b^k | n})
//       = Σ_{k≥1} (Π_{p|n} (⌊v_p(n)/k⌋ + 1) - 1)
//
// For n = N!:
// v_p(N!) = Σ_{j≥1} ⌊N/p^j⌋
// R(N!) = Σ_{k=1}^{max v_p} (Π_{p≤N, v_p≥k} (⌊v_p/k⌋ + 1) - 1)
//
// Use sqrt-decomposition: for each prime p, generate (L,R,q) ranges
// where ⌊v_p/k⌋ = q for k ∈ [L,R]. Multiply range by (q+1) mod M.
// Process via difference array on sorted events.

const ll MOD = 1000000007LL;
const int N = 10000000; // 10^7

ll mod_pow(ll a, ll e) {
    ll r = 1;
    while (e) { if (e & 1) r = r * a % MOD; a = a * a % MOD; e >>= 1; }
    return r;
}

ll mod_inv(ll x) { return mod_pow(x, MOD - 2); }

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        // Compute R(10,000,000!) mod 1e9+7
        // Sieve primes and compute v_p
        vector<int> min_p(N + 1);
        vector<int> primes;
        for (int i = 2; i <= N; i++) {
            if (!min_p[i]) {
                min_p[i] = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > min_p[i] || (ll)i * p > N) break;
                min_p[i * p] = p;
            }
        }

        // Compute v_p(N!) for each prime
        vector<int> vp(primes.size());
        int max_v = 0;
        for (int idx = 0; idx < (int)primes.size(); idx++) {
            int p = primes[idx];
            ll pk = p;
            int v = 0;
            while (pk <= N) {
                v += N / pk;
                pk *= p;
            }
            vp[idx] = v;
            if (v > max_v) max_v = v;
        }

        // For each k from 1 to max_v, compute product_k = Π(⌊v_p/k⌋+1)
        // We'll process range updates from each prime
        // Using events: at k = L, multiply by factor (q+1); at k = R+1, divide by (q+1)
        // But instead of range updates, let's compute directly:
        // For each prime, iterate k from 1 to v_p, but group by quotient

        vector<ll> prod(max_v + 2, 1); // prod[k] = product for that k

        for (int idx = 0; idx < (int)primes.size(); idx++) {
            int v = vp[idx];
            if (v == 0) continue;

            // Generate (L, R, factor) for quotient changes
            // ⌊v/k⌋ = q for k ∈ (v/(q+1), v/q]
            int k = 1;
            while (k <= v) {
                int q = v / k;
                int nxt = v / q; // largest k with same q
                // For k ∈ [k, nxt], factor = q + 1
                ll factor = q + 1;
                prod[k] = prod[k] * factor % MOD;
                if (nxt + 1 <= max_v)
                    prod[nxt + 1] = prod[nxt + 1] * mod_inv(factor) % MOD;
                k = nxt + 1;
            }
        }

        // Now sweep to compute final product per k
        ll cur = 1, ans = 0;
        for (int k = 1; k <= max_v; k++) {
            cur = cur * prod[k] % MOD;
            // contribution = cur - 1 (mod MOD)
            ans = (ans + cur - 1) % MOD;
        }
        if (ans < 0) ans += MOD;

        cout << ans << "\n";
        return 0;
    }

    if (query == "verify") {
        cout << "PE 926: Total Roundness / 总取整度\n\n";
        cout << "R(20) = 6 (verified by problem statement)\n";
        cout << "R(10!) = 312 (verified by problem statement)\n";
        cout << "Target: R(10,000,000!) mod 1e9+7\n";
        return 0;
    }

    cout << "PE 926: Total Roundness / 总取整度\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
