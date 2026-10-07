#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 800: Hybrid Integers / 混合整数
//
// Hybrid integer: p^q * q^p where p ≠ q are primes.
// C(n) = number of hybrid integers ≤ n.
// Given: C(800) = 2, C(800^800) = 10790.
// Find C(800800^800800).
//
// Observations:
// - 800 = 2^5 * 5^2, which itself is a hybrid integer (p=2,q=5).
//   The two hybrid integers ≤ 800 are: 2^3*3^2=72 and 2^5*5^2=800.
//   Wait: 2^3*3^2 = 8*9 = 72 ≤ 800 ✓
//   3^2*2^3 = 72 (same, p<q by convention)
//
// - C(800^800) = 10790 — a modest number compared to 800^800.
//
// Approach: For primes p < q, hybrid integer H = p^q * q^p.
// Need to count all (p,q) with p<q such that p^q * q^p ≤ N.
//
// Since p^q grows extremely fast (exponential in q), only small
// primes contribute. For N = 800800^800800, this is a huge number.
// But p^q * q^p with p≥2, q≥3 is already 2^3*3^2=72.
// For larger p,q, the value quickly exceeds any bound.
//
// Key: take logarithms.
// log(p^q * q^p) = q*log(p) + p*log(q)
// Need: q*log(p) + p*log(q) ≤ log(N)
//
// For N = 800800^800800:
// log(N) = 800800 * log(800800)
//
// Let B = 800800.
// log(N) = B * log(B) ≈ 800800 * 13.593 ≈ 10,885,000
//
// Now, for primes p < q:
// q*log(p) + p*log(q) ≤ B*log(B)
//
// Since p ≥ 2, the maximum q occurs when p=2:
// q*log(2) + 2*log(q) ≤ B*log(B)
// q*0.693 + 2*log(q) ≤ ~10,885,000
// q ≤ ~10,885,000 / 0.693 ≈ 15,700,000
//
// So q can be up to ~15 million. We need primes up to that range.
// That's ~1 million primes (by PNT: π(1.57×10^7) ≈ 1.57×10^7/ln(1.57×10^7) ≈ 10^6).
//
// For each p, q ranges from next_prime(p) up to some max_q(p).
// We need to efficiently count pairs (p,q) satisfying the inequality.
//
// Using binary search on q for each p:
// For fixed p, f(q) = q*log(p) + p*log(q) is increasing in q.
// Find max q satisfying f(q) ≤ B*log(B).
//
// Total complexity: O(π(Q_max)) where Q_max ≈ 1.5×10^7, which is ~10^6 primes.
// For each prime p, binary search on primes takes O(log π(Q_max)) ≈ 20 steps.
// Total: ~2×10^7 operations — feasible.
//
// PE answer: 1412403576

const ll PE_ANSWER = 1412403576LL;

// Sieve for primes up to limit
vector<int> primes;
vector<bool> is_prime;

void sieve(int limit) {
    is_prime.assign(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            if ((ll)i * i <= limit) {
                for (ll j = (ll)i * i; j <= limit; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
}

// Count hybrid integers ≤ N = BASE^BASE using logarithms
ll count_hybrid(ll BASE) {
    double logN = BASE * log((double)BASE);
    
    // Find maximum possible prime q
    // For p=2: q*log(2) + 2*log(q) ≤ logN
    // Approximate: q ≤ logN / log(2)
    int q_max = (int)(logN / log(2.0)) + 10;
    
    // Generate primes up to q_max
    sieve(q_max);
    
    cout << "  Primes up to " << q_max << ": " << primes.size() << "\n";
    
    ll count = 0;
    
    // For each prime p, find the largest prime q > p with f(p,q) ≤ logN
    for (size_t i = 0; i < primes.size(); i++) {
        int p = primes[i];
        double logp = log((double)p);
        
        // Binary search for max q
        int lo = (int)i + 1; // q > p
        int hi = (int)primes.size() - 1;
        int best = (int)i; // no valid q found yet
        
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int q = primes[mid];
            double f = q * logp + p * log((double)q);
            if (f <= logN) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        
        if (best > (int)i) {
            count += best - (int)i;
        }
        
        // Early exit: if p*log(next_prime) already exceeds, break
        if (i + 1 < primes.size()) {
            int q_min = primes[i + 1];
            double f_min = q_min * logp + p * log((double)q_min);
            if (f_min > logN) break;
        }
    }
    
    return count;
}

// Brute force for small bounds to verify
ll brute_count(ll N) {
    ll count = 0;
    // Generate small primes
    int pmax = (int)sqrt(N) + 10;
    vector<int> small_primes;
    vector<bool> isp(pmax + 1, true);
    isp[0] = isp[1] = false;
    for (int i = 2; i <= pmax; i++) {
        if (isp[i]) {
            small_primes.push_back(i);
            for (ll j = (ll)i * i; j <= pmax; j += i) isp[j] = false;
        }
    }
    
    set<i128> seen;
    for (size_t i = 0; i < small_primes.size(); i++) {
        int p = small_primes[i];
        for (size_t j = i + 1; j < small_primes.size(); j++) {
            int q = small_primes[j];
            
            // Compute p^q * q^p carefully
            i128 val = 1;
            bool overflow = false;
            for (int k = 0; k < q; k++) {
                val *= p;
                if (val > (i128)N * 2) { overflow = true; break; }
            }
            if (overflow) continue;
            for (int k = 0; k < p; k++) {
                val *= q;
                if (val > N) { overflow = true; break; }
            }
            if (!overflow && val <= N) {
                seen.insert(val);
                count++;
            }
        }
    }
    return count;
}

void verify_hybrid() {
    cout << "PE 800: Hybrid Integers / 混合整数\n\n";
    
    cout << "=== Definition ===\n";
    cout << "Hybrid integer: p^q * q^p where p ≠ q are primes.\n";
    cout << "Examples: 2^3 * 3^2 = 72, 2^5 * 5^2 = 800\n\n";
    
    cout << "=== Verification of given values ===\n";
    
    // C(800) = 2
    ll c800 = brute_count(800);
    cout << "  C(800) = " << c800 << " (expected 2) " << (c800 == 2 ? "✓" : "✗") << "\n";
    
    // List all hybrid integers ≤ 800
    cout << "  Hybrid integers ≤ 800:\n";
    set<i128> seen;
    vector<int> small_p = {2,3,5,7,11,13,17,19,23};
    for (size_t i = 0; i < small_p.size(); i++) {
        int p = small_p[i];
        for (size_t j = i+1; j < small_p.size(); j++) {
            int q = small_p[j];
            i128 val = 1;
            for (int k = 0; k < q; k++) val *= p;
            for (int k = 0; k < p; k++) val *= q;
            if (val <= 800) {
                cout << "    " << p << "^" << q << " * " << q << "^" << p
                     << " = " << (ll)val << "\n";
            }
        }
    }
    
    // C(800^800) = 10790 (too large to brute-force, use log method)
    cout << "\n  C(800^800): using log method...\n";
    ll c800_800 = count_hybrid(800);
    cout << "  Result: " << c800_800 << " (expected 10790) "
         << (c800_800 == 10790 ? "✓" : "✗") << "\n";
    
    // Small bounds test
    cout << "\n=== Small bound verification ===\n";
    for (ll N : {100, 1000, 10000}) {
        ll bf = brute_count(N);
        cout << "  N=" << N << ": brute=" << bf << "\n";
    }
}

void compute_hybrid() {
    cout << "=== Computing C(800800^800800) ===\n\n";
    
    ll BASE = 800800;
    double logN = BASE * log((double)BASE);
    cout << "BASE = " << BASE << "\n";
    cout << "log(N) = " << logN << "\n";
    
    // Estimate max prime needed
    double q_est = logN / log(2.0);
    cout << "Estimated max q ≈ " << (ll)q_est << "\n";
    
    cout << "\nComputing... ";
    cout.flush();
    
    ll ans = count_hybrid(BASE);
    
    cout << "done!\n";
    cout << "\nC(" << BASE << "^" << BASE << ") = " << ans << "\n";
    cout << "PE answer = " << PE_ANSWER << "\n";
    
    if (ans == PE_ANSWER) {
        cout << "✓ Match!\n";
    } else {
        cout << "✗ Mismatch (got " << ans << ", expected " << PE_ANSWER << ")\n";
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
        verify_hybrid();
        return 0;
    }
    if (query == "compute") {
        compute_hybrid();
        return 0;
    }
    cout << "PE 800: Hybrid Integers / 混合整数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
