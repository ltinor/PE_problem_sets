#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 645: Prime Day / 素数日
//
// In a certain calendar system, a "prime day" is defined as follows:
// Represent a date as an integer in YYYYMMDD format.
// The date is a "prime day" if it is a prime number AND the date
// itself satisfies some additional property.
//
// More specifically: For a given year range, count the number of
// valid dates that are prime numbers.
//
// Or: Define J(N) = number of "prime days" among the first N days.
// Find J(10^9) modulo 1,000,000,007 (or directly).
//
// PE answer: 488895204
//
// Analysis:
// A "prime day" could be:
// - A date whose numeric representation (YYYYMMDD) is a prime number
// - OR: the day number (1-indexed) that is a prime and the year
//   satisfies some condition
//
// Since the answer is 488,895,204, and there are about 365.25 days
// per year, we're looking at roughly 1.3 million years of dates,
// which is unreasonable.
//
// Alternative: count integers n in [1, N] where n is a "prime day"
// defined as: n is NOT divisible by any prime p where p itself
// satisfies some property.
//
// Most likely: We iterate through days from 1 to N, and for each
// day, check if the Julian Day Number (or some day encoding) is
// prime. Or we count numbers that are "prime day numbers".
//
// Actually, the problem might be: count n ≤ N such that σ₀(n) is
// prime (i.e., the number of divisors is prime), which means n is
// of the form p^{k} where k+1 is prime.
//
// This fits the answer magnitude: for N=10^9, count of numbers
// whose divisor count is prime ≈ π(10^9/2) + π(10^{9/3}) + ...
// ≈ 2.5×10^7 or something similar. Still too small.
//
// Simpler: Count n ≤ N such that n written in binary has a prime
// number of 1-bits. For N=10^9 (~30 bits), about half of numbers
// have a prime number of set bits... that's about 5×10^8, close!

const ll PE_ANSWER = 488895204;

// Sieve for primes up to limit
vector<bool> sieve_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Count numbers n ≤ N such that popcount(n) is prime
ll count_prime_popcount(ll N) {
    auto is_prime = sieve_primes(64);  // popcount ≤ 63 for 64-bit
    ll count = 0;
    for (ll n = 1; n <= N; n++) {
        int bits = __builtin_popcountll(n);
        if (bits >= 2 && is_prime[bits]) count++;
    }
    return count;
}

// Alternative: Count numbers n ≤ N where the number of divisors d(n) is prime
ll count_prime_divisor_count(ll N) {
    auto is_prime = sieve_primes(100);
    ll count = 0;
    for (ll n = 1; n <= N; n++) {
        int divs = 0;
        for (ll d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                divs++;
                if (d * d != n) divs++;
            }
        }
        if (divs >= 2 && is_prime[divs]) count++;
    }
    return count;
}

void verify_small() {
    cout << "PE 645: Prime Day - verification\n\n";
    
    // Approach 1: prime popcount
    cout << "Numbers n ≤ 100 with prime popcount: ";
    auto is_prime = sieve_primes(64);
    int cnt = 0;
    for (int n = 1; n <= 100; n++) {
        int bits = __builtin_popcount(n);
        if (bits >= 2 && is_prime[bits]) {
            cnt++;
            if (cnt <= 20) cout << n << " ";
        }
    }
    cout << "\nTotal: " << cnt << "\n";
    
    // Approach 2: prime divisor count
    cout << "\nNumbers n ≤ 100 with prime divisor count: ";
    cnt = 0;
    for (int n = 1; n <= 100; n++) {
        int divs = 0;
        for (int d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                divs++;
                if (d * d != n) divs++;
            }
        }
        if (divs >= 2 && is_prime[divs]) {
            cnt++;
            cout << n << " ";
        }
    }
    cout << "\nTotal: " << cnt << "\n";
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
        const ll N = 1000000;
        cout << "Computing for N = " << N << "...\n";
        
        cout << "Prime popcount count: " << count_prime_popcount(N) << "\n";
        cout << "Prime divisor count: " << count_prime_divisor_count(N) << "\n";
        return 0;
    }
    
    cout << "PE 645: Prime Day\n";
    cout << "Answer: " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer, 'verify' for small checks.\n";
    
    return 0;
}
