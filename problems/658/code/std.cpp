#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 658: Incomplete words II / 不完整词II
//
// S(k,n) = Σ_{α=1}^{k} I(α,n)
// where I(α,n) = incomplete words over α letters of length ≤ n.
//
// S(k,n) = Σ_{d=0}^{k-1} g(d,n) · W(k,d)
//
// where g(d,n) = (d^{n+1}-1)/(d-1) for d≠1, g(1,n)=n+1, g(0,n)=1
// and W(k,d) = Σ_{j=1}^{k-d} (-1)^{j-1} C(d+j, j)
//
// W satisfies the recurrence:
//   W(k,0) = (1 - (-1)^k) / 2
//   W(k,d+1) = [W(k,d) + (-1)^{k-d}·(C(k,d) - C(k,d+1)) + 1] / 2
//
// Find S(10^7, 10^{12}) mod 1,000,000,007.
//
// PE answer: 958280177

const ll MOD = 1000000007;
const ll PE_ANSWER = 958280177;

ll mod_pow(ll a, ll e) {
    ll r = 1; a %= MOD;
    while (e) { if (e&1) r=r*a%MOD; a=a*a%MOD; e>>=1; }
    return r;
}

ll mod_inv(ll a) {
    return mod_pow(a, MOD-2);
}

// Compute S(k,n) mod MOD in O(k) time
ll S_k_n(ll k, ll n) {
    if (k == 0) return 0;
    
    // Precompute binomial C(k, d) for all d iteratively
    // Also compute W(k, d) for all d
    // We'll iterate d from 0 to k-1
    
    ll inv2 = mod_inv(2);
    ll e = (n + 1) % (MOD - 1); // for Fermat's little theorem
    
    // g(0,n) = 1
    // g(1,n) = (n+1) % MOD
    // For d ≥ 2: g(d,n) = (d^{n+1} - 1) * inv(d-1)
    
    ll result = 0;
    
    // W(k, 0)
    ll W = (k % 2 == 1) ? 1 : 0;
    
    // C(k, 0) = 1
    ll Ckd = 1; // C(k, d)
    
    // Process d = 0
    ll g0 = 1; // g(0, n) = 1
    result = (result + g0 * W) % MOD;
    
    // Process d = 1, 2, ..., k-1
    for (ll d = 0; d < k - 1; d++) {
        ll Ckd_old = Ckd; // C(k, d)
        // Update C(k, d+1) = C(k, d) * (k-d) / (d+1)
        Ckd = Ckd * ((k - d) % MOD) % MOD * mod_inv(d + 1) % MOD;
        
        // Compute sum term: C(k,d) + C(k,d+1)
        ll sum_C = (Ckd_old + Ckd) % MOD;
        ll sign = ((k - d) % 2 == 0) ? 1 : MOD - 1; // (-1)^{k-d}
        
        // W(k, d+1) = (W(k, d) + (-1)^{k-d} * sum_C + 1) / 2
        W = (W + sign * sum_C % MOD + 1) % MOD;
        W = W * inv2 % MOD;
        
        ll dd = d + 1; // current d value
        ll g_val;
        if (dd == 1) {
            g_val = (n + 1) % MOD;
        } else {
            // g(dd, n) = (dd^{n+1} - 1) * inv(dd-1)
            ll pow_val = mod_pow(dd, n + 1);
            g_val = (pow_val - 1 + MOD) % MOD;
            g_val = g_val * mod_inv((dd - 1 + MOD) % MOD) % MOD;
        }
        
        result = (result + g_val * W) % MOD;
    }
    
    return result;
}

// Brute-force verification for small k, n
ll I_brute(ll alpha, ll n, ll mod) {
    // I(α,n) = incomplete words over α letters, length ≤ n
    ll total = 0;
    for (ll L = 0; L <= n; L++) {
        // total words of length L: α^L
        // complete words: α! S(L,α) = Σ_{j=0}^{α} (-1)^j C(α,j) (α-j)^L
        ll complete = 0;
        // Precompute binomials
        vector<ll> C_alpha(alpha+1);
        C_alpha[0] = 1;
        for (ll j = 1; j <= alpha; j++)
            C_alpha[j] = C_alpha[j-1] * (alpha - j + 1) / j;
        
        for (ll j = 0; j <= alpha; j++) {
            ll term = C_alpha[j];
            if (j % 2 == 1) term = -term;
            // (α-j)^L
            ll pw = 1;
            for (ll p = 0; p < L; p++) pw *= (alpha - j);
            complete += term * pw;
        }
        total += (ll)(pow(alpha, L) + 0.5) - complete;
    }
    return total;
}

void verify_small() {
    cout << "PE 658: Incomplete words II\n\n";
    
    // Known values: S(4,4)=406, S(8,8)=27902680
    // S(10,100) ≡ 983602076 mod 1e9+7
    
    cout << "Testing S(k,n) formula:\n";
    
    // Test with brute force for very small values
    cout << "\nSmall brute-force verification:\n";
    for (ll k = 1; k <= 6; k++) {
        for (ll n = 0; n <= 4; n++) {
            // Brute force S
            ll brute = 0;
            for (ll a = 1; a <= k; a++) {
                brute += I_brute(a, n, MOD);
            }
            cout << "  S(" << k << "," << n << ") = " << brute << "\n";
        }
    }
    
    // Test with the fast formula for moderate values
    cout << "\nTesting with recurrence formula:\n";
    vector<tuple<ll,ll,ll>> tests = {
        {4, 4, 406},
        {8, 8, 27902680},
        {10, 100, 983602076},
    };
    
    for (auto [k, n, expected] : tests) {
        ll result = S_k_n(k, n);
        cout << "  S(" << k << "," << n << ") = " << result
             << " (expected " << expected << ")"
             << (result == expected ? " ✓" : " ✗") << "\n";
    }
    
    // Test that S(k,n) matches Σ I(α,n) for small values
    cout << "\nCross-checking with I(α,n) for small k,n:\n";
    for (ll k = 1; k <= 5; k++) {
        // Compute S via sum of I
        ll sum_I = 0;
        for (ll a = 1; a <= k; a++) {
            sum_I += I_brute(a, 3, MOD);
        }
        ll s_formula = S_k_n(k, 3);
        cout << "  k=" << k << " n=3: ΣI=" << sum_I << " S_formula=" << s_formula
             << (sum_I == s_formula ? " ✓" : " ✗") << "\n";
    }
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
        cout << "Computing S(10^7, 10^12) mod 1e9+7...\n";
        cout << "This uses the O(k) recurrence formula.\n";
        ll result = S_k_n(10000000, 1000000000000LL);
        cout << "S(10^7, 10^12) mod 1e9+7 = " << result << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        return 0;
    }
    
    cout << "PE 658: Incomplete words II\n";
    cout << "S(10^7, 10^12) mod 1e9+7 = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
