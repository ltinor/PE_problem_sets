#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Compute if denominator of H_n is divisible by p
// Using modular arithmetic - track numerator and denominator separately
// and reduce modulo p at each step (but keep enough info to know divisibility by p)

// Actually, we need to know if p divides the REDUCED denominator.
// Approach: keep track of p-adic valuation of numerator and denominator.

// At each step: H_n = num/den (reduced)
// H_{n+1} = num/den + 1/(n+1) = (num*(n+1) + den) / (den*(n+1))
// After reduction: 
//   new_num = (num*(n+1) + den) / g
//   new_den = den*(n+1) / g
// where g = gcd(num*(n+1) + den, den*(n+1))

// For checking p | den_new, we need the p-adic valuation.
// Let v_p(x) be the exponent of p in x.
// v_p(den_new) = v_p(den) + v_p(n+1) - min(v_p(num*(n+1)+den), v_p(den)+v_p(n+1))
// Actually it's more complex.

// Better: compute everything modulo a power of p (say p^2 or p^3)
// and track the reduced denominator mod p.

// Actually, simplest: for each n, compute H_n as a rational number with
// denominator and numerator taken modulo p^K for sufficiently large K.

// For checking if p divides b_n, we need to check if b_n ≡ 0 mod p.
// b_n = D_n / gcd(D_n, N_n) where D_n is common denom and N_n is numerator.

// Let's track the fraction num/den where we reduce by gcd but only remove
// factors coprime to p. Factors of p are tracked separately via valuations.

struct Frac {
    ll num;  // modulo p^2 or similar (but we need exact for now)
    ll den;  // modulo p^2
    int vnum; // p-adic valuation of actual numerator
    int vden; // p-adic valuation of actual denominator
};

int main() {
    const ll p = 3;
    // We'll track the fraction as num/den (both modulo p), 
    // plus valuations separately
    
    // For each n, we compute: H_n = A_n / B_n
    // We maintain: A_n mod p, B_n mod p, and v_p(A_n), v_p(B_n)
    // However, reduction by gcd affects valuations.
    
    // Alternative: work in the p-adic numbers. 
    // H_n ∈ Z_p iff b_n not divisible by p.
    // Compute H_n mod p^2 or mod p to determine Z_p membership.
    
    // Actually, the simplest correct approach for small n:
    // Track the fraction as a rational and check p-divisibility of den
    // using a "fraction modulo p" technique:
    
    // Let num/den be the current fraction (not necessarily reduced).
    // After each step, reduce by gcd(num,den) but only track:
    // - den_mod_p: den % p
    // - vp: the p-adic valuation of den (in reduced form)
    
    // Hmm, this is still complex. Let me just use Python.
    
    return 0;
}
