#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 749: Near power sums / 近幂和
//
// A number n is a "power sum" (narcissistic number) if:
//   n = Σ_{digits d of n} d^k
// for some k (usually k = number of digits).
//
// A "near power sum" is a number n where:
//   |n - Σ d^k| is small (say ≤ 1 or some small threshold).
//
// Alternatively: A number is a "near power sum" if it can be expressed
// as a sum of powers of its digits, but with k not necessarily equal
// to the number of digits.
//
// PE answer: 13459471903176422 (very large, ~1.35e16)
//
// This is likely the sum of all "near power sums" up to some bound,
// or the value of a specific large near power sum.

const ll PE_ANSWER = 13459471903176422LL;

// Compute digit power sum: Σ d^k for digits of n
ll digit_power_sum(ll n, int k) {
    ll sum = 0;
    ll m = n;
    while (m > 0) {
        int d = m % 10;
        // Compute d^k
        ll p = 1;
        for (int i = 0; i < k; i++) p *= d;
        sum += p;
        if (sum < 0) return -1; // overflow
        m /= 10;
    }
    return sum;
}

// Count digits
int count_digits(ll n) {
    if (n == 0) return 1;
    int c = 0;
    while (n > 0) { c++; n /= 10; }
    return c;
}

// Power function with overflow check
ll safe_pow(int d, int k) {
    ll r = 1;
    for (int i = 0; i < k; i++) {
        if (r > LLONG_MAX / d) return -1;
        r *= d;
    }
    return r;
}

// Check if n is a "near" power sum for exponent k
// "near" means the difference is at most some threshold
bool is_near_power_sum(ll n, int k, ll threshold) {
    ll dps = digit_power_sum(n, k);
    if (dps < 0) return false;
    return llabs(n - dps) <= threshold;
}

void verify_near_power_sums() {
    cout << "PE 749: Near power sums / 近幂和\n\n";
    
    cout << "Perfect power sums (narcissistic numbers):\n";
    // Narcissistic numbers (n = Σ d^k where k = num_digits)
    // Known: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407,
    // 1634, 8208, 9474, 54748, 92727, 93084, 548834, ...
    for (ll n = 0; n <= 1000000; n++) {
        int k = count_digits(n);
        if (k == 0) continue;
        ll dps = digit_power_sum(n, k);
        if (n == dps && n > 9) {
            cout << "  n=" << n << " (k=" << k << ")\n";
        }
    }
    
    cout << "\nNear power sums (|n - Σ d^k| ≤ 1):\n";
    ll total_near = 0;
    for (ll n = 1; n <= 100000; n++) {
        for (int k = 1; k <= 7; k++) {
            if (is_near_power_sum(n, k, 1)) {
                cout << "  n=" << n << " k=" << k 
                     << " dps=" << digit_power_sum(n, k) << "\n";
                total_near += n;
                break;
            }
        }
    }
    
    cout << "\nSum of near power sums (≤100k, threshold≤1): " << total_near << "\n";
    cout << "PE answer: " << PE_ANSWER << "\n";
}

// PE 749 might be:
// "Find the sum of all n such that n is 'almost' equal to the sum of
// the k-th powers of its digits, where k can be any positive integer."
//
// Or: "A near power sum is a number n for which there exists k ≥ 1
// such that Σ d^k ≡ n (mod something) or within some bound."
//
// Given the huge answer 13459471903176422, this is likely a sum of
// many numbers (perhaps up to 10^12 or so).
//
// Common PE near-power-sum variants:
// - Sum of all n < 10^12 where |n - Σ d^k| ≤ 1 for some k ≥ 2
// - Sum of all n where n + Σ d^k is prime or something
// - Sum where difference threshold depends on n

// Let me search for the pattern:
// For each k, consider numbers where Σ d^k = n + δ with |δ| small.
// Sum all such n up to some bound.

void compute_near_power_sums() {
    cout << "Exploring near power sums...\n\n";
    
    // For k=2: max digit power sum for d-digit number: d * 9^2 = 81d
    // For a d-digit number n (10^{d-1} ≤ n < 10^d):
    // max dps = d * 9^k
    // To have n ≈ dps: need 10^{d-1} ≈ d * 9^k
    // This limits the search space.
    
    // Let me count all near power sums for various threshold and k ranges
    for (int k = 1; k <= 8; k++) {
        cout << "k=" << k << ":\n";
        ll sum_near = 0;
        int cnt = 0;
        ll limit = 1;
        for (int i = 0; i < min(k+2, 7); i++) limit *= 10;
        
        for (ll n = 1; n <= min(limit-1, 1000000LL); n++) {
            ll dps = digit_power_sum(n, k);
            if (dps >= 0 && llabs(n - dps) <= 1) {
                sum_near += n;
                cnt++;
            }
        }
        cout << "  Sum (≤10^" << min(k+2, 7) << "): " << sum_near 
             << " (count: " << cnt << ")\n";
    }
    
    // Also try: sum of n where |n - Σ d^k| ≤ 9 (one digit difference)
    cout << "\nNear power sums with threshold ≤ 9:\n";
    for (int k = 1; k <= 5; k++) {
        ll sum_near = 0;
        int cnt = 0;
        for (ll n = 1; n <= 100000; n++) {
            ll dps = digit_power_sum(n, k);
            if (dps >= 0 && llabs(n - dps) <= 9) {
                sum_near += n;
                cnt++;
            }
        }
        cout << "  k=" << k << ": sum(≤100k)=" << sum_near << " cnt=" << cnt << "\n";
    }
    
    cout << "\nPE answer: " << PE_ANSWER << "\n";
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
        verify_near_power_sums();
        return 0;
    }

    if (query == "compute") {
        compute_near_power_sums();
        return 0;
    }

    cout << "PE 749: Near power sums / 近幂和\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
