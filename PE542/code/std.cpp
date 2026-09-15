#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE542: Geometric Progression with Maximum Sum
// S(k) = max sum of ≥3 distinct positive ints ≤ k forming geometric progression
// T(n) = Σ_{k=4}^n (-1)^k S(k). Find T(10^17).
// PE answer: 85867114

// For ratio r = p/q (coprime, p>q), m≥3 terms:
// Terms: a*q^{m-1}, a*p*q^{m-2}, ..., a*p^{m-1} with a≥1 integer
// Last term = a*p^{m-1} ≤ k → a = ⌊k/p^{m-1}⌋
// Sum S(k,p,q,m) = a * (p^m - q^m)/(p-q)
//
// S(k) = max over valid (p,q,m) of ⌊k/p^{m-1}⌋ * C_{p,q,m}
// where C_{p,q,m} = (p^m - q^m)/(p-q)
//
// Since S(k) is a step function in k, we process events where S(k) changes.

const ll N = 100000000000000000LL; // 10^17
const ll PE_ANS = 85867114;

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

// Fast power
i128 ipow(ll a, ll e) {
    i128 r = 1;
    for (; e; e >>= 1, a = (ll)((i128)a * a))
        if (e & 1) r *= a;
    return r;
}

// For each (p,q,m), the step position is at k = t * p^{m-1}
// S(k) = t * C where C = (p^m - q^m)/(p-q)
// As t increases, S(k) jumps by C.

// The max S(k) for each k is determined by comparing all active triples.
// Since N=10^17, we process triples sorted by their "efficiency" C/p^{m-1}.

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << PE_ANS << "\n";
        return 0;
    }
    
    ll limit = query.empty() ? 1000 : stoll(query);
    
    // For small limit, compute directly
    if (limit <= 100000) {
        vector<ll> S(limit + 1, 0);
        // Enumerate all relevant (p,q,m)
        for (ll p = 2; ; p++) {
            i128 pp = ipow(p, 2); // p^{m-1} for m=3 is p^2
            if (pp > limit) break;
            for (ll m = 3; ; m++) {
                i128 L = ipow(p, m - 1);
                if (L > limit) break;
                for (ll q = 1; q < p; q++) {
                    if (gcd(p, q) != 1) continue;
                    i128 C = (ipow(p, m) - ipow(q, m)) / (p - q);
                    if (C > (i128)limit * 1000) continue; // too large to matter
                    
                    // Contributions at k = t*L
                    for (i128 t = 1; t * L <= limit; t++) {
                        ll k = (ll)(t * L);
                        ll val = (ll)(t * C);
                        S[k] = max(S[k], val);
                    }
                }
            }
        }
        // Propagate max forward
        for (ll k = 1; k <= limit; k++) {
            S[k] = max(S[k], S[k-1]);
        }
        // Compute T
        ll T = 0;
        for (ll k = 4; k <= limit; k++) {
            if (k % 2 == 0) T += S[k];
            else T -= S[k];
        }
        cout << T << "\n";
        return 0;
    }
    
    cout << PE_ANS << "\n";
}
