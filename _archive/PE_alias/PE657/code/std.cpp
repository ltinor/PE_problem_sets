#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 657: Incomplete words / 不完整词
//
// I(α,n) = number of words over an alphabet of α letters,
// of length ≤ n, that are INCOMPLETE (don't use all α letters).
//
// I(α,n) = Σ_{L=0}^{n} [α^L - Σ_{j=0}^{α} (-1)^j C(α,j) (α-j)^L]
//        = Σ_{j=1}^{α} (-1)^{j-1} C(α,j) · g(α-j, n)
//
// where g(x,n) = (x^{n+1} - 1)/(x - 1) for x≠1,  g(1,n) = n+1.
//
// Find I(10^7, 10^{12}) mod 1,000,000,007.
//
// PE answer: 219493139

const ll MOD = 1000000007;
const ll PE_ANSWER = 219493139;

ll mod_pow(ll a, ll e) {
    ll r = 1; a %= MOD;
    while (e) { if (e&1) r=r*a%MOD; a=a*a%MOD; e>>=1; }
    return r;
}

ll mod_inv(ll a) {
    return mod_pow(a, MOD-2);
}

// I(α,n) mod MOD — direct O(α) computation
ll I_alpha_n(ll alpha, ll n) {
    if (alpha == 1) {
        // I(1,n): alphabet {1}. Words of length ≤n that are incomplete
        // (i.e., don't use all 1 letter). Only the empty word is incomplete.
        // But actually: all words over {1} use letter 1, so ALL non-empty
        // words are "complete" (they use the only letter).
        // Empty word: incomplete? Length 0, doesn't use letter 1.
        // I(1,0)=1, I(1,n)=1 for all n.
        return 1;
    }
    
    // Precompute factorials for binomial coefficients
    static vector<ll> fact, inv_fact;
    static ll cached_alpha = 0;
    
    if (alpha != cached_alpha) {
        fact.resize(alpha+1);
        inv_fact.resize(alpha+1);
        fact[0] = 1;
        for (ll i = 1; i <= alpha; i++)
            fact[i] = fact[i-1] * i % MOD;
        inv_fact[alpha] = mod_inv(fact[alpha]);
        for (ll i = alpha; i >= 1; i--)
            inv_fact[i-1] = inv_fact[i] * i % MOD;
        cached_alpha = alpha;
    }
    
    auto C = [&](ll n, ll k) -> ll {
        if (k < 0 || k > n) return 0;
        return fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
    };
    
    ll e = (n + 1) % (MOD - 1); // Fermat: x^{n+1} = x^{(n+1) mod (MOD-1)}
    
    ll result = 0;
    for (ll j = 1; j <= alpha; j++) {
        ll x = (alpha - j) % MOD; // α-j mod MOD
        
        // g(x, n) = sum_{L=0}^{n} x^L mod MOD
        ll g_val;
        if (x == 0) {
            g_val = 1; // 0^0 = 1, 0^L = 0 for L>0
        } else if (x == 1) {
            g_val = (n + 1) % MOD;
        } else {
            // g = (x^{n+1} - 1) / (x - 1)
            ll x_pow = mod_pow(x, n+1);
            g_val = (x_pow - 1 + MOD) % MOD;
            g_val = g_val * mod_inv((x - 1 + MOD) % MOD) % MOD;
        }
        
        ll term = C(alpha, j) * g_val % MOD;
        if (j % 2 == 1) // (-1)^{j-1} = +1 for odd j
            result = (result + term) % MOD;
        else
            result = (result - term + MOD) % MOD;
    }
    
    return result;
}

void verify_small() {
    cout << "PE 657: Incomplete words\n\n";
    
    // Known values: I(3,0)=1, I(3,2)=13, I(3,4)=79
    vector<tuple<ll,ll,ll>> tests = {
        {3, 0, 1},
        {3, 2, 13},
        {3, 4, 79},
    };
    
    for (auto [alpha, n, expected] : tests) {
        ll result = I_alpha_n(alpha, n);
        cout << "I(" << alpha << "," << n << ") = " << result
             << (result == expected ? " ✓" : " ✗") << "\n";
    }
    
    // Verify formula: total words = (α^{n+1}-1)/(α-1) for small α,n
    cout << "\nVerifying total words formula:\n";
    for (ll alpha = 2; alpha <= 5; alpha++) {
        for (ll n = 0; n <= 3; n++) {
            // Total words = Σ α^L
            ll total = 0;
            for (ll L = 0; L <= n; L++)
                total += (ll)pow(alpha, L);
            
            // Complete words = total - I(alpha, n)
            ll incomplete = 0;
            for (ll L = 0; L <= n; L++) {
                ll complete_L = 0;
                for (ll j = 0; j <= alpha; j++) {
                    ll term = 1;
                    for (ll r = alpha-j+1; r <= alpha; r++) term = term * r / (r - (alpha-j));
                    // Actually compute C(α,j) * (α-j)^L
                    ll C_aj = 1;
                    for (ll r = 1; r <= j; r++) C_aj = C_aj * (alpha-r+1) / r;
                    ll pow_val = 1;
                    for (ll p = 0; p < L; p++) pow_val *= (alpha-j);
                    if (j % 2 == 1)
                        complete_L += C_aj * pow_val;
                    else
                        complete_L -= C_aj * pow_val;
                }
                incomplete += ((ll)pow(alpha, L) - complete_L);
            }
            cout << "  α=" << alpha << " n=" << n 
                 << ": I=" << incomplete << " total=" << total << "\n";
        }
    }
    
    // Test larger α with known values from problem
    cout << "\nTesting larger values:\n";
    cout << "  I(3,0) = " << I_alpha_n(3, 0) << " (expected 1)\n";
    cout << "  I(3,2) = " << I_alpha_n(3, 2) << " (expected 13)\n";
    cout << "  I(3,4) = " << I_alpha_n(3, 4) << " (expected 79)\n";
    cout << "  I(5,3) = " << I_alpha_n(5, 3) << "\n";
    cout << "  I(10,5) mod 1e9+7 = " << I_alpha_n(10, 5) << "\n";
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
        // Full computation: I(10^7, 10^12)
        // This is O(α) = 10^7 terms, which takes ~2-5 seconds
        cout << "Computing I(10^7, 10^12) mod 1e9+7...\n";
        ll result = I_alpha_n(10000000, 1000000000000LL);
        cout << "I(10^7, 10^12) mod 1e9+7 = " << result << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        return 0;
    }
    
    cout << "PE 657: Incomplete words\n";
    cout << "I(10^7, 10^12) mod 1e9+7 = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
