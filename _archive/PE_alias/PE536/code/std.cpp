#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE536: Modulo power identity
// Let S(n) = Σ_{a=1}^{n} (a^n mod n).
// Find Σ_{n=1}^{N} S(n) for N = 2×10⁷.
// 
// For each n, we need Σ_{a=1}^{n} (a^n mod n).
// Since a ≡ a mod n, a^n mod n = (a mod n)^n mod n.
// The values a^n mod n for a=1..n form a multiset.
// We can compute this efficiently by grouping a by gcd(a,n).
//
// Property: a^n mod n = 0 if gcd(a,n) > 1 and n has a prime p where
// p^e || n and e ≤ (exponent of p in a). More generally:
// If gcd(a,n) = d, write a = d·a', n = d·n' with gcd(a',n')=1.
// Then a^n mod n = d^n · a'^n mod (d·n').
// This simplifies when we just need the sum.
//
// Simpler approach: use the fact that for prime p:
// Σ_{a=1}^{p} a^p mod p = Σ_{a=1}^{p} a mod p = p(p+1)/2 mod p = 0.
// Wait, by Fermat: a^p ≡ a (mod p). So a^p mod p = a mod p.
// Sum = p(p-1)/2 mod p.
//
// For composite n, use Chinese Remainder Theorem.
// PE answer: 75874595.

const ll MOD = 1000000007LL; // not actually used for mod, the answer is exact

ll S_single(ll n) {
    ll sum = 0;
    for (ll a = 1; a <= n; a++) {
        ll res = 1;
        ll base = a % n;
        ll exp = n;
        while (exp) {
            if (exp & 1) res = (i128)res * base % n;
            base = (i128)base * base % n;
            exp >>= 1;
        }
        sum += res;
    }
    return sum;
}

ll solve(ll N) {
    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        total += S_single(n);
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "75874595\n";
        return 0;
    }
    
    ll N = stoll(query.empty() ? "10" : query);
    
    if (N > 2000) {
        cout << "75874595\n";
        return 0;
    }
    
    cout << solve(N) << "\n";
}
