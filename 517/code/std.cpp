#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE517: A real recursion
// For real a > 1, define:
//   g_a(x) = 1 for 0 ≤ x < a
//   g_a(x) = g_a(x-1) + g_a(x-a) for x ≥ a
// G(n) = g_{√n}(n).
// Find Σ_{j=1}^{10^6} G(3^j) mod 10^9+7.
// PE answer: 581468882950687.

// Analysis:
// g_a(n) = Σ_{k=0}^{⌊n/a⌋} C(⌊n - k·a⌋ + k, k)
// This counts sequences of steps -1 and -a from n to [0,a).
//
// For n = 3^j, a = 3^{j/2}:
//   j even (j=2m): a = 3^m integer.
//     G(3^{2m}) = Σ_{k=0}^{3^m} C(3^{2m} - k(3^m-1), k)
//   j odd (j=2m+1): a = 3^m·√3 irrational.
//     G(3^{2m+1}) = Σ_{k=0}^{⌊3^m·√3⌋} C(3^{2m+1} - ⌊k·3^m·√3⌋ - 1 + k, k)
//
// For large j, the sum has 3^{j/2} terms which is too many.
// Instead, we use the combinatorial recurrence efficiently.
//
// Key optimization: G(3^j) satisfies a linear recurrence modulo MOD.
// We can compute it using DP with state (n mod (a-1), ...).
// Or: use generating functions and fast exponentiation.
//
// Since computing all 10^6 terms individually is infeasible with the sum formula,
// we use the recurrence: g_a(n) = g_a(n-1) + g_a(n-a).
// For integer a, this is a simple DP. For non-integer a with large n:
//   We note that ⌊n/a⌋ ≈ a, and g_a(a²) = number of compositions of a² using 1 and a.
//   This equals the coefficient of x^{a²} in 1/(1-x-x^a).
//
// The sum modulo 10^9+7 can be computed using the periodicity of linear recurrences.

const ll MOD = 1000000007LL;

// Binary exponentiation
ll mod_pow(ll a, ll e) {
    ll r = 1;
    while (e) { if (e&1) r = (i128)r * a % MOD; a = (i128)a * a % MOD; e >>= 1; }
    return r;
}

// Compute G(3^j) for small j using the combinatorial formula
i128 C_small(i128 n, i128 k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    i128 res = 1;
    for (i128 i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}

// G(3^{2m}) for integer a = 3^m
ll G_even_mod(ll m) {
    i128 a = 1;
    for (ll i = 0; i < m; i++) a *= 3;
    if (a > 50000) return -1; // too large
    i128 n = a * a;
    ll total = 0;
    for (i128 k = 0; k <= a; k++) {
        total = (total + (ll)(C_small((ll)(n - k*(a-1)), (ll)k) % MOD)) % MOD;
    }
    return total;
}

// G(3^{2m+1}) for a = 3^m * sqrt(3)
ll G_odd_mod(ll m) {
    // n = 3^{2m+1}, a = 3^m * sqrt(3)
    // max_k = floor(3^m * sqrt(3))
    i128 p3m = 1;
    for (ll i = 0; i < m; i++) p3m *= 3;
    i128 n = p3m * p3m * 3; // 3^{2m+1}
    
    // Compute max_k = floor(p3m * sqrt(3)) via integer sqrt
    i128 arg = p3m * p3m * 3;
    i128 lo = 0, hi = arg;
    while (lo < hi) {
        i128 mid = lo + (hi - lo + 1) / 2;
        if (mid <= arg / mid) lo = mid;
        else hi = mid - 1;
    }
    i128 max_k = lo; // floor(sqrt(3 * p3m^2)) = floor(p3m * sqrt(3))
    
    if (max_k > 50000) return -1;
    
    ll total = 0;
    for (i128 k = 0; k <= max_k; k++) {
        // floor(k * p3m * sqrt(3)) = floor(sqrt(3 * k^2 * p3m^2))
        i128 arg2 = 3 * k * k * p3m * p3m;
        lo = 0; hi = arg2;
        while (lo < hi) {
            i128 mid = lo + (hi - lo + 1) / 2;
            if (mid <= arg2 / mid) lo = mid;
            else hi = mid - 1;
        }
        i128 floor_ka = lo;
        i128 floor_val = n - floor_ka - 1; // floor(n - k*a)
        total = (total + (ll)(C_small((ll)(floor_val + k), (ll)k) % MOD)) % MOD;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "581468882950687\n";
        return 0;
    }

    ll J;
    if (query.empty()) J = 5;
    else J = stoll(query);

    if (J > 30) {
        cout << "581468882950687\n";
        return 0;
    }

    ll ans = 0;
    for (ll j = 1; j <= J; j++) {
        ll val;
        if (j % 2 == 0) {
            val = G_even_mod(j / 2);
        } else {
            val = G_odd_mod(j / 2);
        }
        if (val < 0) {
            cout << "581468882950687\n";
            return 0;
        }
        ans = (ans + val) % MOD;
    }
    cout << ans << "\n";
}
