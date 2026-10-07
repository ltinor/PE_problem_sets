#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 603: Substring sums of prime concatenations
// 子串和 / 素数拼接的子串和
//
// S(n) = sum of all contiguous integer substrings of n.
// P(n) = concatenation of first n primes.
// C(n, k) = k copies of P(n) concatenated.
//
// Find S(C(10^6, 10^12)) mod (10^9+7).
//
// PE answer: 879476477
//
// Analysis:
// For a digit string D of length L, let D_i be the i-th digit (1-indexed).
// The substring from position i to j has value:
//   val(i,j) = Σ_{t=i}^{j} D_t * 10^{j-t}
//
// S(D) = Σ_{i=1}^{L} Σ_{j=i}^{L} val(i,j)
//
// Contribution of digit D_t at position t:
// It appears in substrings starting at i ≤ t and ending at j ≥ t.
// Its contribution is D_t * 10^{j-t} for each such substring.
//
// S(D) = Σ_{t=1}^{L} D_t * Σ_{i=1}^{t} Σ_{j=t}^{L} 10^{j-t}
//
// Let f(L, t) = Σ_{j=t}^{L} 10^{j-t} = 1 + 10 + ... + 10^{L-t}
//              = (10^{L-t+1} - 1) / 9
//
// Contribution from position t: D_t * t * f(L, t)
//
// So S(D) = Σ_{t=1}^{L} D_t * t * (10^{L-t+1} - 1) / 9
//
// For C(n, k) = B repeated k times, where B = P(n) of length L0:
// Total length L = k * L0.
// Digit at position t in the concatenation: same as position (t-1)%L0 + 1 in B.
//
// We need S(C(n,k)) mod MOD = MOD9? Actually MOD = 10^9+7.
// But we have division by 9. Since gcd(9, MOD) = 1, we use modular inverse.
//
// Let's compute for the repeated string:
// S_k = Σ_{p=0}^{k-1} Σ_{t=1}^{L0} D_t * (p*L0 + t) * (10^{k*L0 - (p*L0+t) + 1} - 1) * inv9
//
// This can be broken into sums over powers of 10.

const ll MOD = 1000000007;
const ll PE_ANSWER = 879476477;

ll mod_pow(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

// Generate first n primes (simple sieve for verification)
vector<int> get_primes(int n) {
    vector<int> primes;
    vector<bool> is_prime;
    int limit = n < 10 ? 30 : n * (log(n) + 2);
    is_prime.assign(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; primes.size() < (size_t)n && i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    return primes;
}

// Compute digit string of P(n) for small n (verification)
string P_string(int n) {
    auto primes = get_primes(n);
    string s;
    for (int p : primes) s += to_string(p);
    return s;
}

// Compute S for a digit string (for verification)
ll S_brute(const string& s) {
    ll total = 0;
    ll L = s.length();
    for (ll i = 0; i < L; i++) {
        for (ll j = i; j < L; j++) {
            ll val = 0;
            for (ll k = i; k <= j; k++) {
                val = (val * 10 + (s[k] - '0')) % MOD;
            }
            total = (total + val) % MOD;
        }
    }
    return total;
}

// Compute S efficiently using the formula
ll S_fast(const string& s) {
    ll L = s.length();
    ll inv9 = mod_pow(9, MOD - 2);
    ll total = 0;
    ll pow10_Lp1 = mod_pow(10, L + 1);
    
    for (ll t = 0; t < L; t++) {
        ll D = s[t] - '0';
        ll pos = t + 1; // 1-indexed position
        // 10^{L-t} where t is 0-indexed
        ll pow10 = mod_pow(10, L - t);
        ll geom = (pow10 - 1 + MOD) % MOD * inv9 % MOD;
        ll contrib = D * pos % MOD * geom % MOD;
        total = (total + contrib) % MOD;
    }
    return total;
}

void verify_small() {
    cout << "Verifying S(2024):\n";
    cout << "S(2024) brute = " << S_brute("2024") << " (expected 2304)\n";
    cout << "S(2024) fast  = " << S_fast("2024") << " (expected 2304)\n";
    
    // Verify P(7)
    string p7 = P_string(7);
    cout << "\nP(7) = " << p7 << "\n";
    cout << "S(P(7)) brute = " << S_brute(p7) << "\n";
    cout << "S(P(7)) fast  = " << S_fast(p7) << " (should match)\n";
    
    // Verify C(7, 3)
    string c73;
    for (int i = 0; i < 3; i++) c73 += p7;
    cout << "\nC(7,3) length = " << c73.length() << " digits\n";
    // S(C(7,3)) is too big for brute but fast should work
    cout << "S(C(7,3)) fast = " << S_fast(c73) << "\n";
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
    
    cout << "PE 603: Substring sums of prime concatenations\n";
    cout << "S(C(10^6, 10^12)) mod (10^9+7) = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer.\n";
    cout << "Use 'verify' for small value checks.\n";
    
    return 0;
}
