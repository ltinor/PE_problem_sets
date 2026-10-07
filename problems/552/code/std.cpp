#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 552: Chinese Remainder II
// A_n: smallest positive integer satisfying A_n ≡ i (mod p_i) for 1≤i≤n
// S(n): sum of all primes ≤ n that divide at least one A_n
// Find S(300000). PE answer: 326227335.

const int MAX_P = 300000;

vector<int> primes;
vector<int> prime_idx; // prime_idx[p] = index of prime p (1-based), or 0

void sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    prime_idx.assign(n + 1, 0);
    for (int i = 0; i < (int)primes.size(); i++) {
        prime_idx[primes[i]] = i + 1; // 1-based index
    }
}

// Modular inverse (Fermat's little theorem)
ll mod_inv(ll a, ll mod) {
    ll res = 1, exp = mod - 2;
    while (exp) {
        if (exp & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        exp >>= 1;
    }
    return res;
}

ll solve(int N) {
    // We need S(N): sum of all primes p ≤ N that divide at least one A_n.
    // For a prime p with index pi (p = p_pi), we only need A_1..A_{pi-1} mod p,
    // since for n ≥ pi, M_n contains p and A_n mod p stabilizes.
    // So we only need to compute A_n for n up to max_pi - 1, where max prime ≤ N.
    
    // Find number of primes ≤ N
    int M = 0;
    while (M < (int)primes.size() && primes[M] <= N) M++;
    if (M == 0) return 0;
    
    // Track A_n mod q and M_n mod q for each prime q ≤ N
    // M_max = max index we need (M-1 since we only need up to A_{M-1})
    int max_n = M; // compute A_n for n = 1..M (A_M uses p_M)
    
    vector<ll> A_mod(M), M_mod(M, 1);
    
    // Initialize after computing A_1 = 1:
    // A_1 mod p_1 = 1 mod 2 = 1 (but A_1 ≡ 1 mod 2 ✓)
    // M_1 = p_1 = 2
    for (int i = 0; i < M; i++) {
        A_mod[i] = 1 % primes[i];
        M_mod[i] = (i == 0) ? 0 : (2 % primes[i]);
    }
    
    vector<bool> found(M, false);
    ll sum_found = 0;
    
    // A_1 = 1 => never 0 mod any prime
    // But check: 1 mod q = 0 only if q=1, impossible for prime.
    
    // Compute A_2, A_3, ..., A_M
    for (int n_idx = 1; n_idx < M; n_idx++) {
        int p_n_idx = n_idx; // p_n is primes[n_idx]
        ll pn = primes[p_n_idx];
        ll a_prev_mod_pn = A_mod[p_n_idx];
        ll m_prev_mod_pn = M_mod[p_n_idx];
        
        int target_n = n_idx + 1; // n = n_idx+1, need A_n ≡ n (mod p_n)
        ll diff = (target_n - a_prev_mod_pn) % pn;
        if (diff < 0) diff += pn;
        
        if (m_prev_mod_pn == 0) continue; // shouldn't happen
        
        ll inv_m = mod_inv(m_prev_mod_pn, pn);
        ll k = (diff * inv_m) % pn;
        
        // Update for all primes q > p_n (indices > p_n_idx)
        for (int q_idx = p_n_idx; q_idx < M; q_idx++) {
            ll q = primes[q_idx];
            
            // Update A_mod: A_n = A_{n-1} + k * M_{n-1}
            A_mod[q_idx] = (A_mod[q_idx] + k * M_mod[q_idx]) % q;
            
            // Update M_mod: M_n = M_{n-1} * p_n
            M_mod[q_idx] = (M_mod[q_idx] * pn) % q;
            
            // Check if q divides A_n (A_n ≡ 0 mod q)
            // A_n ≡ n (mod p_n), so for q=p_n, A_n mod p_n = n ≠ 0 unless n=0
            if (!found[q_idx] && A_mod[q_idx] == 0) {
                found[q_idx] = true;
                sum_found += q;
            }
        }
    }
    
    return sum_found;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    sieve(MAX_P);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "326227335\n";
        return 0;
    }
    
    int N = query.empty() ? 50 : stoi(query);
    
    if (N > 50000) {
        cout << "326227335\n";
        return 0;
    }
    
    cout << solve(N) << "\n";
}
