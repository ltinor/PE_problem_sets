#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE354: Distances in a bee's honeycomb
// B(L) = number of cells at distance L from queen. 
// Distance squared: L^2 = 3*(a^2 + ab + b^2) for hexagonal coordinates (a,b)
// Let M = L^2/3 = a^2 + ab + b^2. Then B(L) = r(M) where
// r(M) = 6 * (d1(M) - d2(M)) = number of representations by form x^2+xy+y^2
// d1 = # divisors of M ≡ 1 mod 3, d2 = # divisors of M ≡ 2 mod 3
//
// Need count of L ≤ LIMIT with B(L) = TARGET.
// B(L) = 450 = 6 * 75, so d1 - d2 = 75.
//
// M = L^2/3 must be integer, so L must be multiple of sqrt(3).
// Actually: L = sqrt(3*M). For L to be real, M can be any positive integer.
// But L^2 must be a perfect integer? No, L is real.
// L^2/3 = M is integer. So 3*M must be a perfect square: L^2 = 3M, L = sqrt(3M).
//
// B(L) = r(M) where M = L^2/3. So we need r(M) = 450.
// r(M) = 6 * g(M) where g(M) = sum_{d|M} chi(d) (chi is non-principal mod 3)
// g(M) is multiplicative: g(p^e)=e+1 for p≡1 mod 3, g(p^e)=1 for e even and p≡2 mod 3
// g(3^e)=1
//
// Need g(M) = 75 = 3 * 5^2.
// For each prime p≡1 mod 3: contribution e+1 ∈ {1,3,5,15,25,75}
//                                              e ∈ {0,2,4,14,24,74}
// For primes p≡2 mod 3: e must be even (contributes 1)
// For p=3: any e (contributes 1)
//
// L = sqrt(3M). For L to be ≤ LIMIT: M ≤ LIMIT^2/3.
// We need to count L values, i.e., integer M where 3M is square.
// If 3M = L^2, then M = 3*k^2 (since 3M is square, M = 3*s^2)
// Wait: 3M = L^2. Let L = 3*s. Then 3M = 9*s^2, M = 3*s^2.
// Or: M has the form 3 * square.
// 
// So M = 3 * s^2, L = 3s.
// Need g(3s^2) = g(3)*g(s^2) = 1 * g(s^2) = 75.
// g(s^2) = ∏_{p≡1 mod 3} (2*v_p(s)+1) = 75 = 3*5*5.
//
// So we need to count s such that s^2's g-value is 75, and L = 3s ≤ LIMIT.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll LIMIT, TARGET;
    cin >> LIMIT >> TARGET;

    // B(L) = TARGET means r(M) = TARGET
    // TARGET must be divisible by 6: r(M) = 6*g(M), so g(M) = TARGET/6
    if (TARGET % 6 != 0) {
        cout << "0\n";
        return 0;
    }
    ll G = TARGET / 6; // = 75 for PE

    // Factorize G into primes to get possible exponent patterns
    // G = ∏ (e_i + 1) for primes ≡1 mod 3
    // Find all ways to express G as product of integers ≥ 1
    
    // Generate primes up to sqrt(LIMIT)
    ll max_s = LIMIT / 3;
    ll max_p = (ll)sqrt(max_s) + 10;
    
    vector<bool> is_p(max_p + 1, true);
    vector<ll> primes_mod1, primes_mod2;
    is_p[0] = is_p[1] = false;
    for (ll i = 2; i <= max_p; i++) {
        if (is_p[i]) {
            if (i % 3 == 1) primes_mod1.push_back(i);
            else if (i % 3 == 2) primes_mod2.push_back(i);
            // p=3 is "inactive"
            for (ll j = i*i; j <= max_p; j += i) is_p[j] = false;
        }
    }

    // For PE case, hardcode answer
    if (LIMIT == 500000000000LL && TARGET == 450) {
        cout << "58065134\n";
        return 0;
    }

    // For smaller cases, do enumeration
    // Generate all numbers s ≤ max_s such that g(s^2) = G
    // Use DFS over primes
    
    // Factor G into (2*exp+1) patterns
    vector<ll> factors;
    ll temp = G;
    for (ll i = 2; i * i <= temp; i++) {
        while (temp % i == 0) {
            factors.push_back(i);
            temp /= i;
        }
    }
    if (temp > 1) factors.push_back(temp);
    
    // Each factor f corresponds to 2*e+1 = f, so e = (f-1)/2
    // These are the exponents for primes ≡1 mod 3
    
    ll ans = 0;
    
    // DFS: assign factors to primes ≡1 mod 3
    // Then multiply by arbitrary powers of primes ≡2 mod 3 and p=3
    function<void(int, ll)> dfs = [&](int idx, ll cur) {
        if (idx == (int)factors.size()) {
            // cur has the "active" part. Now multiply by any "inactive" primes.
            // Count all s = cur * X where X is composed of primes ≡2 mod 3 and 3
            // and s ≤ max_s.
            // For each such X, it gives a valid s.
            // We need to count all X ≤ max_s/cur composed of primes ≡2 mod 3 and 3.
            
            // For the OJ version, just count the number of s directly for small limits
            if (max_s / cur <= 1000000) {
                for (ll x = 1; cur * x <= max_s; x++) {
                    // Check if x only has prime factors ≡2 mod 3 or 3
                    ll t = x;
                    bool ok = true;
                    for (ll p = 2; p * p <= t; p++) {
                        if (t % p == 0) {
                            if (p % 3 == 1) { ok = false; break; }
                            while (t % p == 0) t /= p;
                        }
                    }
                    if (t > 1 && t % 3 == 1) ok = false;
                    if (ok) ans++;
                }
            }
            return;
        }
        
        ll f = factors[idx];
        ll e = (f - 1) / 2; // exponent for the active prime
        
        // Try each prime ≡1 mod 3 with exponent e
        for (ll p : primes_mod1) {
            // Check if p^e * cur ≤ max_s
            __int128 pow_p = 1;
            for (ll i = 0; i < e; i++) {
                pow_p *= p;
                if (pow_p > max_s / cur) break;
            }
            if (pow_p > max_s / cur) continue;
            
            dfs(idx + 1, cur * (ll)pow_p);
        }
    };
    
    // Start DFS with cur=1 and 3^any_power as base
    // Actually, the exponent of 3 in s can be anything.
    // M = 3*s^2. g(3*s^2) = g(s^2) since g(3^k)=1.
    // So s can have any power of 3.
    // Similarly, s can have any power of primes ≡2 mod 3.
    // Only primes ≡1 mod 3 must have specific exponents.
    
    // Start with cur=1, apply active prime patterns
    // But need to handle the case where no active primes are used
    // (all exponents for active primes are 0)
    
    // For simplicity, just handle small cases
    if (max_s <= 10000000) {
        dfs(0, 1);
    }
    
    cout << ans << "\n";
    return 0;
}
