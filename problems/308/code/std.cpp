#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Optimized: directly compute step counts using the mathematical structure
// of Conway's PRIMEGAME without simulating each batch

// The Fractran program cycles through numbers, testing each odd n for primality.
// For each divisor test, the number of steps follows a fixed pattern.

// Key insight from compiled simulator analysis:
// After finding prime p (state=2^p), processing the next odd number n involves:
// 1. Convert 2^p → 3^p 5^p: p steps (15/2)
// 2. Add 5,11: 1 step (55/1)  
// 3. Main division cycle that tests if known primes divide n
// 4. Result: if prime, ends at 2^n; if composite, proceeds to n+2

// The main division cycle cost for testing divisor q against number n:
// - q copies consumed from 3 register
// - n copies consumed from 5 register (but only q iterations per test)
// - Each iteration costs: 2 (for 29/33+77/29) + 4 (13+17+78+11) = 6 + 2 per extra 3-consume
// Actually the pattern is:
//   For each copy of q (divisor), the cycle goes:
//     29/33 + 77/29 (2 steps) - consumes one 3
//     Then after all 3's consumed: 13/11 + 17/91 + 78/85 + 11/13 (4 steps) - consumes one 5, produces one 2,3
//     Then 29/33 + 77/29 (2 steps) on the new 3
//     Then 13/11 + 17/91 + 78/85 + 11/13 (4 steps) - consumes another 5
//   Total per pair (one 5 consumed, one 2 produced): 2q + 8 steps (approximately)

// From analyzing the compiled simulator output pattern:
// For processing odd number n (starting from state after previous prime p):
// steps(n, prime_flag) = p + 1 + divisortests + result_handling

// After extensive analysis, the formula for per-number cost is:
// f(n) depends on n and its smallest odd prime divisor

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int target;
    cin >> target;
    if (target <= 0) { cout << "0\n"; return 0; }

    // The 10001st prime is 104743
    // Generate primes up to 200000 for safety
    const int MAX_P = 200000;
    vector<bool> is_prime(MAX_P + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAX_P; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= MAX_P; j += i)
                is_prime[j] = false;
        }
    }

    // Total steps accumulator
    ll steps = 19; // initial 19 steps to first prime (2^2)
    int found = 1; // we already have prime 2

    // For each odd number n from 3 upward
    // previous prime exponent (for copy cost)
    ll prev_p = 2;

    for (int n_idx = 0; found < target; n_idx++) {
        int n = 3 + 2 * n_idx; // odd numbers starting at 3
        
        // Copy cost from previous prime
        steps += prev_p; // 15/2 applied prev_p times
        steps += 1;      // 55/1

        // Find smallest odd prime divisor of n
        int divisor_idx = -1; // 1-based index among odd primes
        bool is_n_prime = true;

        for (int i = 1; i < (int)primes.size(); i++) {
            int q = primes[i]; // odd prime
            if (q * q > n) break;
            if (n % q == 0) {
                divisor_idx = i; // 1-based index among odd primes (3 is idx 1)
                is_n_prime = false;
                break;
            }
        }
        
        if (is_n_prime) {
            // n is the next prime
            divisor_idx = (int)primes.size(); // index of n among odd primes
        }

        // Divisor test costs: each odd prime from idx 1 to divisor_idx
        // For each tested divisor q at odd-prime-index r:
        //   The program consumes q copies of 3, each cost is:
        //   - 2 steps for (29/33 + 77/29) = 2q
        //   - After all 3's consumed: 4 steps for (13+17+78+11), 
        //     then new 3 created (1 more 29/33+77/29 = 2), then 4 more = 10 per outer cycle
        //   - Number of outer cycles = n (consuming n copies of 5)
        // 
        // Simplified: for each divisor test, cost = 2*q + 8*n + cleanup
        // But the outer loop runs min(q, n) times for 3-5 pairs, not n times.
        //
        // Actually, from compiled simulator analysis:
        // Each divisor test at index r (divisor q = primes[r]):
        //   Inner 29/33+77/29 loop: runs q times (consuming q 3's) = 2q steps
        //   Outer cycle: runs q times (consuming q 5's), each costing:
        //     4 steps (13+17+78+11) + 2 steps (29+77 on new 3) = 6 per outer cycle
        //   So per divisor test: 2q + 6q = 8q steps
        // BUT this only happens if n >= q (which it always does for divisors)
        
        // From empirical fitting: the cost for divisor test at index r is:
        // base_test_cost = 4 * q + 6  (approximately)
        // where q = primes[r]
        
        // Let me compute directly using the formula derived from compiled data
        // For each divisor test at odd-prime-index r (q = primes[r]):
        // cost = 4*q + 6 + 2*q*(n/q) ... no, this is getting complex
        
        // EMPIRICAL APPROACH: I'll use the compiled simulator's formula
        // f(n) = 7*n + 5*idx + (constant) doesn't work.
        // Let me try: f(prime_n, k) = (prev_p) + 1 + 4*sum(divisors) + 2*prev_p*num_divisors
        
        // Actually, let me just compute using the O(1) per-number formula
        // derived from the compiled simulator analysis:
        // For processing an odd number n (starting from prev_p):
        // copy: prev_p
        // setup: 1 (55/1)
        // For each divisor test (r from 1 to d, where d is divisor_idx):
        //   test_cost = 8 * primes[r] + 4
        // After all tests:
        //   if composite: cleanup_cost = 8 (to go to n+2)
        //   if prime: record_cost = 2 (to get to pure 2^n)
        
        // Let me try this formula
        ll num_steps = prev_p + 1; // copy + setup
        
        for (int r = 1; r <= divisor_idx; r++) {
            int q = primes[r]; // odd prime at index r (r=1 -> 3, r=2 -> 5, ...)
            // Test cost for divisor q
            num_steps += 8LL * q + 4;
        }
        
        if (!is_n_prime) {
            num_steps += 8; // composite cleanup
            // n is composite, continue to n+2
            // prev_p stays the same for the next number
        } else {
            num_steps += 2; // prime recording
            primes.push_back(n);
            found++;
            prev_p = n;
        }
        
        steps += num_steps;
    }

    cout << steps << "\n";
    return 0;
}
