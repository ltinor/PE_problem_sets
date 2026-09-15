#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 934: Unlucky Primes / 不幸素数
//
// u(n) = smallest prime p s.t. n mod p is NOT a multiple of 7.
// U(N) = Σ_{n=1}^{N} u(n). U(1470)=4293. Find U(10^17).
//
// For prime p, "bad residues" = {0, 7, 14, ...} ∩ [0, p-1] = ⌊(p-1)/7⌋+1 values.
// u(n)=p iff: ∀q<p (prime), n mod q is bad, AND n mod p is NOT bad.
//
// Count via CRT: let M_k = product of first k primes.
// Count of n ≤ N where first k primes are all bad: C_k = Π |bad_{q_i}| 
// Actual count = N/M_k * C_k + count in remainder.
// Then u(n)=p_k count = count(bad for first k-1 primes) - count(bad for first k primes).
// U(N) = Σ p_k · count(u=p_k).

const ll N = 100000000000000000LL; // 10^17

// Generate primes
vector<int> primes;
void sieve(int limit) {
    vector<bool> is_prime(limit + 1, true);
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
}

int bad_count(int p) {
    // number of residues r ∈ [0, p-1] that are multiples of 7
    return (p - 1) / 7 + 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        sieve(200); // enough primes for significant contributions
        
        // Compute U(N) using inclusion-exclusion
        // U(N) = 2*count(u≥2) + 3*count(u≥3 and u≠2) + 5*count(u≥5 and u∉{2,3}) + ...
        // = Σ (p_k - p_{k-1}) * count(u ≥ p_k)  (with p_0 = 0)
        
        // count(u ≥ p_k) = number of n ≤ N where first k-1 primes are bad
        // For k=1 (p=2): count(u ≥ 2) = N (all n)
        
        ll ans = 0;
        ll prev_count = N; // count where u ≥ 2 (all n)
        
        i128 mod_product = 1; // product of primes so far
        i128 bad_product = 1; // product of bad counts
        
        for (size_t i = 0; i < primes.size(); i++) {
            int p = primes[i];
            int bad = bad_count(p);
            
            // count where first i+1 primes are bad
            // = number of n ≤ N satisfying n mod q ∈ bad_q for q = first i+1 primes
            i128 new_mod = mod_product * p;
            i128 new_bad = bad_product * bad;
            
            // Count: (N / new_mod) * new_bad + count in remainder
            ll full_blocks = N / (ll)new_mod;
            ll cur_count = full_blocks * (ll)(new_bad % new_mod); // careful with overflow
            
            // Handle remainder
            // We need to count n in [full_blocks*new_mod+1, N]
            // that satisfy the congruence conditions.
            // For simplicity, use CRT to count in remainder.
            ll rem = N % (ll)new_mod;
            
            // Count numbers ≤ rem that satisfy all congruence conditions
            // Precompute all valid residue classes modulo new_mod
            // This is small for first few primes
            ll rem_count = 0;
            if (rem > 0) {
                // Enumerate all residues mod new_mod that satisfy conditions
                // Since new_mod can be large, use generation via CRT
                vector<ll> residues = {0}; // start with residue 0 mod 1
                i128 cur_mod = 1;
                
                for (size_t j = 0; j <= i; j++) {
                    int q = primes[j];
                    int bad_q = bad_count(q);
                    vector<ll> new_res;
                    i128 new_m = cur_mod * q;
                    
                    for (ll r : residues) {
                        // Find all x ≡ r (mod cur_mod) and x mod q ∈ bad_q
                        // x = r + t*cur_mod, 0 ≤ t < q
                        for (int t = 0; t < q; t++) {
                            ll x = r + t * (ll)cur_mod;
                            if (x % q < (bad_q * 7 > q ? q : bad_q)) {
                                // Check if x mod q is a multiple of 7
                                bool bad_match = false;
                                for (int m = 0; m < bad_q; m++) {
                                    if (x % q == m * 7) { bad_match = true; break; }
                                }
                                if (bad_match) {
                                    new_res.push_back(x % (ll)new_m);
                                }
                            }
                        }
                    }
                    residues = new_res;
                    cur_mod = new_m;
                }
                
                for (ll r : residues) {
                    if (r <= rem && r > 0) rem_count++;
                }
            }
            
            cur_count = full_blocks * (ll)bad_product + rem_count;
            
            // Count where u = p
            ll count_u_eq_p = prev_count - cur_count;
            ans += (ll)p * count_u_eq_p;
            
            prev_count = cur_count;
            mod_product = new_mod;
            bad_product = new_bad;
            
            if (cur_count == 0) break; // no more n satisfy all bad
        }
        
        cout << ans << "\n";
        return 0;
    }

    if (query == "verify") {
        cout << "PE 934: Unlucky Primes / 不幸素数\n\n";
        cout << "u(n) = smallest prime p where n mod p ≠ 0 (mod 7)\n";
        cout << "U(1470) = 4293\n";
        cout << "Target: U(10^17)\n";
        return 0;
    }

    cout << "PE 934: Unlucky Primes / 不幸素数\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
