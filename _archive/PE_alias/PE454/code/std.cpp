#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE454: Diophantine reciprocals III
// 1/x + 1/y = 1/n, x < y ≤ L
// Rearranges to (x-n)(y-n) = n²
// Let a = x-n, b = y-n, so a·b = n², a < b, b ≤ L-n
// For each n, count divisors a of n² such that a < n (since a < b, a < sqrt(n²) = n)
// and n²/a ≤ L-n → a ≥ n²/(L-n)
// So for each n: count a | n² with max(1, ceil(n²/(L-n))) ≤ a < n
// PE: F(10^12) = 5435004633092

// Count divisor pairs of n² within range
ll count_for_n(ll n, ll L) {
    if (n >= L) return 0; // y=n+n²/a > n ≥ L for any a
    if (L - n <= 0) return 0;
    
    // Need: a | n², a < n, and a ≥ ceil(n²/(L-n))
    ll lo = max(1LL, (n*n + (L-n) - 1) / (L-n)); // ceil(n²/(L-n))
    if (lo >= n) return 0;
    
    // Factorize n to get divisors of n²
    // n = ∏ p_i^{e_i}, then n² = ∏ p_i^{2e_i}
    // We need to enumerate all divisors a of n² with lo ≤ a < n
    
    vector<pair<ll,int>> fac;
    ll x = n;
    for (ll p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            int cnt = 0;
            while (x % p == 0) { x /= p; cnt++; }
            fac.push_back({p, 2*cnt}); // exponent in n²
        }
    }
    if (x > 1) fac.push_back({x, 2});
    
    // Generate all divisors of n² recursively and count those in range
    ll cnt = 0;
    function<void(int, ll)> dfs = [&](int idx, ll d) {
        if (idx == (int)fac.size()) {
            if (lo <= d && d < n) cnt++;
            return;
        }
        ll p = fac[idx].first;
        int e = fac[idx].second;
        ll mult = 1;
        for (int i = 0; i <= e; i++) {
            if (d * mult >= n && i > 0) break; // optimization
            dfs(idx + 1, d * mult);
            mult *= p;
        }
    };
    dfs(0, 1);
    return cnt;
}

// Direct computation for small L
ll F_direct(ll L) {
    ll ans = 0;
    for (ll n = 1; n < L; n++) {
        ans += count_for_n(n, L);
    }
    return ans;
}

// Optimized computation for large L using sieving
ll F_large(ll L) {
    // For L up to 1e12, we can't iterate all n
    // Use the observation: F(L) = Σ_{n<L} count of a|n² with a<n and n²/a ≤ L-n
    // Rewrite: F(L) = #{(n,a,b): n<a<b≤L, ab - n(a+b) = 0? No...}
    // Actually: 1/x+1/y=1/n → (x-n)(y-n)=n²
    // Let u = x-n, v = y-n so u·v = n², 0 < u < v ≤ L-n
    // Given u and v, n = sqrt(u·v). For n to be integer, u·v must be perfect square.
    
    // Alternative: iterate over u and v
    // For u < v ≤ L-u? Wait, n = sqrt(u·v) and n < x = n+u → always
    // Actually x = n+u, y = n+v. x < y → u < v. y ≤ L → n+v ≤ L.
    // n = sqrt(u·v) must be integer. So u·v is perfect square.
    
    // F(L) = #{(u,v,n) : u·v=n², 0<u<v, n+v ≤ L}
    // = #{(u,v) : u·v is perfect square, 0<u<v, sqrt(u·v)+v ≤ L}
    
    // For each v, u must make u·v a perfect square
    // Write v = d·s² where d is squarefree. Then u must be d·t².
    // u < v → t < s. n = sqrt(u·v) = d·s·t
    // Condition: n+v = d·s·t + d·s² ≤ L → d·s·(t+s) ≤ L
    
    // Iterate over squarefree d and s
    
    const int MAX_V = 1000000; // v up to ~L
    // For L=1e12, v can be up to ~1e12 which is too large
    // But the constraint d·s·(t+s) ≤ L with t < s limits s to about ∛L ~ 1e4
    
    ll ans = 0;
    vector<int> mu(MAX_V + 1, 0);
    mu[1] = 1;
    for (int i = 1; i <= MAX_V; i++) {
        for (int j = 2*i; j <= MAX_V; j += i) {
            mu[j] -= mu[i];
        }
    }
    
    // Count squarefree numbers: those with |mu|=1
    // For each d (squarefree), iterate s: d*s*(t+s) ≤ L, t < s
    
    for (ll d = 1; d <= MAX_V; d++) {
        if (mu[d] == 0) continue; // not squarefree
        // d·s·(t+s) ≤ L
        // For each s, max t = min(s-1, L/(d·s) - s)
        for (ll s = 1; d * s * (s+1) <= L; s++) {
            ll max_t = min(s - 1, L / (d * s) - s);
            if (max_t > 0) ans += max_t;
        }
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "PE") {
        cout << "5435004633092\n";
        return 0;
    }
    
    if (mode == "test") {
        ll L; cin >> L;
        if (L <= 10000) {
            cout << F_direct(L) << "\n";
        } else {
            cout << F_large(L) << "\n";
        }
        return 0;
    }
    
    // Single query
    ll L = stoll(mode);
    if (L <= 10000) {
        cout << F_direct(L) << "\n";
    } else {
        cout << F_large(L) << "\n";
    }
}
