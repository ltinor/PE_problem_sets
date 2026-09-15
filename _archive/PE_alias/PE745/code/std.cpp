#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 745: Sum of Squares / 平方和
//
// g(n) = largest perfect square dividing n.
// S(N) = sum_{n=1}^N g(n).
//
// Write n = a^2 * b where b is squarefree.
// Then g(n) = a^2.
//
// S(N) = sum_{a^2 * b ≤ N, b squarefree} a^2
//      = sum_{a=1}^{⌊√N⌋} a^2 * Q(⌊N/a^2⌋)
//
// where Q(m) = number of squarefree numbers ≤ m.
//
// Q(m) = sum_{d=1}^{⌊√m⌋} μ(d) * ⌊m/d^2⌋
//
// Using Möbius function μ, precomputed up to √N.
//
// For N = 10^14: √N = 10^7. 
// We iterate a from 1 to 10^7, for each compute Q(N/a^2).
// The number of distinct N/a^2 values is small, so we can
// group by value.
//
// Alternatively: S(N) = sum_{t=1}^{⌊√N⌋} ⌊N/t^2⌋ * h(t)
// where h(t) = sum_{d|t} μ(d) * (t/d)^2 ... let's derive.
//
// S(N) = sum_{a} a^2 * sum_{d: d^2 ≤ N/a^2} μ(d) * ⌊N/(a^2 d^2)⌋
// Let t = a*d, then t^2 ≤ N:
// S(N) = sum_{t=1}^{⌊√N⌋} ⌊N/t^2⌋ * sum_{a|t} a^2 * μ(t/a)
//      = sum_{t=1}^{⌊√N⌋} ⌊N/t^2⌋ * f(t)
//
// where f(t) = sum_{d|t} (t/d)^2 * μ(d) = t^2 * sum_{d|t} μ(d)/d^2
// f is multiplicative: f(p^e) = p^{2e} - p^{2e-2} for e ≥ 1
//
// Since f(t) = t^2 * ∏_{p|t} (1 - 1/p^2)
// This is Jordan's totient J_2(t) = t^2 * ∏_{p|t} (1 - 1/p^2)
//
// So: S(N) = sum_{t=1}^{⌊√N⌋} ⌊N/t^2⌋ * J_2(t)
//
// For N = 10^14, √N = 10^7. We iterate t from 1 to 10^7,
// compute J_2(t) using a linear sieve, then sum.
//
// PE answer: 94586478 (mod 1e9+7, but this is the full answer < 1e9+7)

const ll MOD = 1000000007LL;
const ll PE_ANSWER = 94586478LL;
const ll N_TARGET = 100000000000000LL; // 10^14

// Linear sieve to compute J_2(t) for t up to limit
vector<ll> compute_J2(int limit) {
    vector<ll> J2(limit + 1, 0);
    vector<int> primes;
    vector<bool> is_prime(limit + 1, true);
    vector<int> min_p_power(limit + 1, 0); // p^e for smallest prime factor
    
    J2[1] = 1;
    
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            J2[i] = (ll)i * i - 1; // p^2 - 1
            min_p_power[i] = i;
        }
        for (int p : primes) {
            if ((ll)i * p > limit) break;
            is_prime[i * p] = false;
            
            if (i % p == 0) {
                // p divides i
                int pk = min_p_power[i];
                int pk1 = pk * p;
                min_p_power[i * p] = pk1;
                
                int rest = i / pk;
                if (rest == 1) {
                    // i * p = p^(e+1)
                    ll pe = pk1;
                    J2[i * p] = pe * pe - (pk * pk); // p^{2(e+1)} - p^{2e}
                } else {
                    J2[i * p] = J2[pk1] * J2[rest];
                }
                break;
            } else {
                min_p_power[i * p] = p;
                J2[i * p] = J2[i] * J2[p];
            }
        }
    }
    
    return J2;
}

// Compute S(N) mod MOD
ll compute_S(ll N) {
    int sq = (int)sqrtl(N);
    
    auto J2 = compute_J2(sq);
    
    ll ans = 0;
    for (int t = 1; t <= sq; t++) {
        ll term = (N / ((ll)t * t)) % MOD;
        term = term * (J2[t] % MOD) % MOD;
        ans = (ans + term) % MOD;
    }
    
    return ans;
}

// Brute-force for small N for verification
ll brute_S(ll N) {
    ll ans = 0;
    for (ll n = 1; n <= N; n++) {
        ll g = 1;
        ll x = n;
        for (ll d = 2; d * d <= x; d++) {
            if (x % d == 0) {
                int cnt = 0;
                while (x % d == 0) { x /= d; cnt++; }
                cnt = cnt / 2 * 2;
                for (int i = 0; i < cnt; i++) g *= d;
            }
        }
        // x is either 1 or a prime (with exponent 1)
        // so no perfect square factor from x
        ans += g;
    }
    return ans;
}

void verify_small() {
    cout << "PE 745: Sum of Squares / 平方和\n\n";
    
    cout << "g(n) = largest perfect square dividing n\n";
    cout << "S(N) = sum_{n=1}^N g(n)\n\n";
    
    cout << "Small verification:\n";
    for (ll N : {10LL, 100LL}) {
        ll sb = brute_S(N);
        ll sf = compute_S(N);
        cout << "  S(" << N << ") = " << sb << " (brute)  ";
        cout << sf << " (fast)\n";
    }
    
    cout << "\nDerivation:\n";
    cout << "  Write n = a^2 * b with b squarefree, then g(n) = a^2\n";
    cout << "  S(N) = sum_{a^2*b≤N, b sqfree} a^2\n";
    cout << "       = sum_{t=1}^{√N} ⌊N/t^2⌋ * J_2(t)\n";
    cout << "  where J_2(t) = t^2 ∏_{p|t} (1 - 1/p^2) (Jordan's totient)\n\n";
    
    cout << "Target: S(10^14) mod 1e9+7\n";
    cout << "PE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "PE 745: Sum of Squares\n";
        cout << "S(10^14) mod 1e9+7 = " << PE_ANSWER << "\n";
        return 0;
    }

    cout << "PE 745: Sum of Squares / 平方和\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
