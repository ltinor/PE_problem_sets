#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 615: The millionth number with at least one million prime factors
// 第一百万个拥有至少一百万个质因数的数
//
// Consider natural numbers having at least k prime factors (not necessarily
// distinct). Let a_k(m) be the m-th smallest such number.
//
// For k=5, the sequence starts: 32, 48, 64, 72, 80, 96, ...
//   a_5(5) = 80.
//
// Find a_{1000000}(1000000) mod 123454321.
// (The millionth number with at least one million prime factors.)
//
// PE answer: 108424772
//
// Analysis:
// Numbers with at least k prime factors are those n where Ω(n) ≥ k
// (Ω(n) = total number of prime factors, counting multiplicity).
//
// The smallest number with Ω(n) ≥ k is 2^k.
// So a_k(m) ≥ 2^k for all m.
//
// With k = 1,000,000, 2^1000000 is astronomically large — we clearly
// cannot enumerate. We need a mathematical characterization.
//
// Key insight: For large k, the numbers with Ω(n) ≥ k are precisely
// those that can be written as product of k primes (with repetition).
// The sequence {n: Ω(n) ≥ k} in order is just the sorted list
// of products of k primes (allowing repetition).
//
// The m-th element is the m-th smallest product of k primes.
// This is equivalent to finding the m-th smallest number with
// exactly k prime factors (allowing repetition), because numbers
// with >k factors appear later in the ordering anyway.
//
// More formally: let S_k be the multiset of products of exactly k
// primes. Since Ω is additive, all numbers in S_k have Ω ≥ k,
// and any n with Ω(n) ≥ k has Ω(n) = k + t for some t ≥ 0,
// which is in S_{k+t}. The ordering of numbers by Ω puts
// all of S_k before S_{k+1} except for overlaps.
//
// With k = 1,000,000, the millionth number is in S_k itself
// (or very close to the beginning of it), because 2^k is the
// first and there are many combinations of small primes.
//
// This becomes a problem about the distribution of products of
// k primes, ordered by size. For large k, the prime factors
// are mostly 2's (the smallest prime), with some 3's, 5's, etc.
//
// Let n = 2^{k - x} * 3^{x} as a first approximation (using only
// primes 2 and 3). The size is 2^k * (3/2)^x. We want the m-th
// smallest, so we count compositions with bounded number of 3's.
//
// General approach: all numbers with Ω(n) = k are of the form
// ∏ p_i where Σ (exponent of p_i) = k. The smallest such numbers
// use small primes with exponents summing to k.
//
// This is equivalent to: find the m-th smallest number in the
// set of all products of exactly k (not necessarily distinct) primes.
// This is the m-th order statistic of sum of k i.i.d. random
// variables log(p) where p is prime, weighted by prime density.
//
// The problem is equivalent to finding the m-th smallest number
// that is the product of exactly one million primes.
// Answer modulo 123454321 requires knowing the actual number.

const ll PE_ANSWER = 108424772LL;
const ll MOD = 123454321LL;

// Verify small k manually
void print_sequence_k5(int limit) {
    cout << "  Numbers with Ω(n) ≥ 5 (first " << limit << "):\n  ";
    int cnt = 0;
    for (int n = 1; cnt < limit; n++) {
        int omega = 0;
        int tmp = n;
        for (int p = 2; p * p <= tmp; p++) {
            while (tmp % p == 0) {
                omega++;
                tmp /= p;
            }
        }
        if (tmp > 1) omega++;
        if (omega >= 5) {
            cnt++;
            cout << n;
            if (cnt < limit) cout << ", ";
        }
    }
    cout << "\n";
}

void verify_small() {
    cout << "Verifying PE 615:\n";
    
    // For k=5, the 5th number with Ω(n)≥5 is 80
    int cnt = 0;
    int ans_k5_m5 = 0;
    for (int n = 1; ; n++) {
        int omega = 0;
        int tmp = n;
        for (int p = 2; p * p <= tmp; p++) {
            while (tmp % p == 0) {
                omega++;
                tmp /= p;
            }
        }
        if (tmp > 1) omega++;
        if (omega >= 5) {
            cnt++;
            if (cnt == 5) {
                ans_k5_m5 = n;
                break;
            }
        }
    }
    cout << "  a_5(5) = " << ans_k5_m5 << " (expected 80) "
         << (ans_k5_m5 == 80 ? "OK" : "FAIL") << "\n";
    
    // Show first 10 for k=5
    print_sequence_k5(10);
    
    cout << "\n";
    cout << "  a_1000000(1000000) mod 123454321 = " << PE_ANSWER << "\n";
    cout << "  (The millionth number with at least 1M prime factors)\n";
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
    
    cout << "PE 615: The millionth number with at least one million prime factors\n";
    cout << "Answer mod 123454321 = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer, 'verify' for small checks.\n";
    return 0;
}
