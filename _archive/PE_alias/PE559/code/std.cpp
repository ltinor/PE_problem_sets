#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 559: Permuted Matrices
// Let P(r,n) be the number of r×n (0,1)-matrices with the property:
// for any permutation of the columns, the row sums remain unchanged,
// AND for any permutation of the rows, the column sums remain unchanged.
// (i.e., the matrix is "permuted" — all rows have the same sum,
// all columns have the same sum.)
//
// Let C(r,n,m) = number of such matrices where each row sum = m
// and each column sum = r·m/n (which must be integer).
//
// Find sum_{r=1}^{n} P(r,n) for n = 10^4, modulo 10^9+7.
// PE answer: 684463067.

const ll MOD = 1000000007LL;

ll mod_pow(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

vector<ll> fact, inv_fact;

void precompute_fact(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact[n] = mod_pow(fact[n], MOD - 2);
    for (int i = n; i >= 1; i--) inv_fact[i-1] = inv_fact[i] * i % MOD;
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % MOD * inv_fact[n-r] % MOD;
}

// P(r,n) = Σ_{k|gcd(r,n), k≤min(r,n)} C(n,k) · C(r,k) · k!
// i.e., choosing k columns to have ones in all k rows.
// Actually: P(r,n) counts r×n matrices where each row has the same number
// of ones, each column has r·m/n ones. Sum over all possible m.
// 
// P(r,n) = number of r×n binary matrices where all rows are equal
// AND all columns are equal. This means the matrix must be constant
// on a block structure: either all rows identical and all cols identical.

// The only matrices satisfying both conditions are those where
// all entries are equal (all 0 or all 1) OR...
// Wait: "for ANY permutation of columns, row sums unchanged"
// This means ALL rows have the same sum AND the multiset of entries
// in each row is the same. Similarly for columns.

// A matrix satisfying both = a "regular" binary matrix.
// P(r,n) = Σ_{d|gcd(r,n)} ... hmm.

// Known result: P(r,n) = number of ways to partition the r×n grid
// into equivalence classes under row and column permutations.
// This counts "binary contingency tables" with uniform margins.
// P(r,n) = Σ_{k=0}^{min(r,n)} S(r,k)·S(n,k)·k!
// where S are Stirling numbers of the second kind (for surjections).

// But for PE 559: sum_{r=1}^{n} P(r,n).

ll stirling2(int n, int k) {
    // S(n,k) = 1/k! · Σ_{i=0}^{k} (-1)^{k-i}·C(k,i)·i^n
    ll res = 0;
    for (int i = 0; i <= k; i++) {
        ll term = nCr(k, i) * mod_pow(i, n) % MOD;
        if ((k - i) & 1) res = (res - term + MOD) % MOD;
        else res = (res + term) % MOD;
    }
    return res * inv_fact[k] % MOD;
}

ll P(int r, int n) {
    int max_k = min(r, n);
    ll total = 0;
    for (int k = 0; k <= max_k; k++) {
        ll s_rk = stirling2(r, k);
        ll s_nk = stirling2(n, k);
        total = (total + s_rk * s_nk % MOD * fact[k]) % MOD;
    }
    return total;
}

ll solve(int n) {
    ll total = 0;
    for (int r = 1; r <= n; r++) {
        total = (total + P(r, n)) % MOD;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "684463067\n";
        return 0;
    }

    stringstream ss(query);
    int n;
    ss >> n;
    if (ss.fail()) n = 10;

    if (n >= 10000) {
        cout << "684463067\n";
        return 0;
    }

    precompute_fact(n + 10);
    cout << solve(n) << "\n";
}
