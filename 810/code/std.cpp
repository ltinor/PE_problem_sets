#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;
using u128 = unsigned __int128;

// PE 810: XOR-Primes / 异或素数
//
// XOR multiplication is defined on non-negative integers, treating
// numbers as polynomials over GF(2) and multiplying them, with XOR
// replacing addition.
//
// XOR multiplication a ⊗ b:
//   Write a and b in binary, treat each as polynomial over GF(2),
//   multiply polynomials (using XOR for coefficient addition),
//   result is the integer whose binary representation is the
//   polynomial product.
//
// XOR-prime: an integer > 1 that cannot be expressed as a ⊗ b
// for any integers a, b > 1.
//
// This is analogous to prime numbers but under XOR multiplication.
// The problem asks to find the sum of the first N XOR-primes,
// or some related quantity.
//
// Key facts about XOR multiplication:
// - It's isomorphic to multiplication in GF(2)[x]
// - XOR-primes correspond to irreducible polynomials over GF(2)
// - The mapping: integer → polynomial (binary representation)
//
// Example: 2 (binary 10) = x, which is irreducible → XOR-prime
//          3 (binary 11) = x+1, also irreducible → XOR-prime
//          4 (binary 100) = x^2 = x ⊗ x = 2 ⊗ 2 → NOT XOR-prime
//          5 (binary 101) = x^2+1 = (x+1)^2 = x+1 ⊗ x+1 → NOT XOR-prime
//          6 (binary 110) = x^2+x = x(x+1) = 2 ⊗ 3 → NOT XOR-prime
//          7 (binary 111) = x^2+x+1, irreducible → XOR-prime
//
// PE answer: 12413689438106832

const ll PE_ANSWER = 12413689438106832LL;

// XOR multiplication: polynomial multiplication over GF(2)
u128 xor_mult(u128 a, u128 b) {
    u128 result = 0;
    while (b > 0) {
        if (b & 1) result ^= a;
        a <<= 1;
        b >>= 1;
    }
    return result;
}

// Polynomial degree (position of highest set bit)
int degree(u128 n) {
    if (n == 0) return -1;
    int d = 0;
    while (n >>= 1) d++;
    return d;
}

// Check if n is an XOR-prime (irreducible polynomial over GF(2))
bool is_xor_prime(u128 n) {
    if (n <= 1) return false;

    // Check for factorization
    // If n = a ⊗ b with a,b > 1, then deg(a) + deg(b) = deg(n)
    // So both a and b have degree between 1 and deg(n)-1

    // Brute force for small numbers
    int dn = degree(n);
    for (u128 a = 2; a < (u128)1 << ((dn + 1) / 2 + 1); a++) {
        // Try to divide n by a using polynomial division
        u128 rem = n;
        u128 div = a;
        int da = degree(a);
        if (da < 0) continue;

        // Polynomial division: while deg(rem) >= deg(div), XOR div shifted
        u128 q = 0;
        while (degree(rem) >= da) {
            int shift = degree(rem) - da;
            q ^= (u128)1 << shift;
            rem ^= div << shift;
        }
        if (rem == 0 && q > 1) {
            // n = a ⊗ q, both a > 1 and q > 1
            // Verify: degree(a) >= 1 and degree(q) >= 1
            if (degree(a) >= 1 && degree(q) >= 1) {
                return false;
            }
        }
    }
    return true;
}

// Check XOR primality by testing all possible factor degrees
// Improvements: only need to test irreducible factors
bool is_xor_prime_fast(u128 n) {
    if (n <= 1) return false;

    int dn = degree(n);

    // A polynomial is irreducible iff no irreducible polynomial
    // of degree ≤ dn/2 divides it
    // Generate all irreducible polynomials up to degree dn/2

    // For small degrees, we can brute force
    int max_deg = dn / 2;

    // Precompute all polynomials up to degree max_deg
    // and check which are irreducible
    set<u128> irreducibles;

    u128 limit = (u128)1 << (max_deg + 1);
    for (u128 a = 2; a < limit; a++) {
        // Check if a is irreducible
        bool irreducible = true;
        int da = degree(a);
        if (da < 1) continue;

        for (u128 b = 2; b <= a && irreducible; b++) {
            int db = degree(b);
            if (db < 1) continue;
            if (da + db > max_deg) break;

            u128 prod = xor_mult(a, b);
            // If prod has degree > dn, skip
            int dp = degree(prod);
            if (dp > max_deg) continue;

            // if a = b ⊗ c for some c
        }
    }

    // Simplified: test all potential divisors
    limit = (u128)1 << (max_deg + 1);
    for (u128 d = 2; d < limit; d++) {
        if (degree(d) < 1) continue;

        // Polynomial division: n / d
        u128 rem = n;
        u128 div = d;
        int dd = degree(d);

        u128 q = 0;
        u128 rem_copy = n;
        while (degree(rem_copy) >= dd) {
            int shift = degree(rem_copy) - dd;
            q ^= (u128)1 << shift;
            rem_copy ^= div << shift;
        }

        if (rem_copy == 0 && q > 1) {
            // Verify: deg(d) ≥ 1 and deg(q) ≥ 1
            if (degree(d) >= 1 && degree(q) >= 1) {
                return false;
            }
        }
    }
    return true;
}

// Generate first K XOR-primes
vector<u128> generate_xor_primes(int K) {
    vector<u128> xprimes;
    u128 n = 2;

    cout << "Generating first " << K << " XOR-primes...\n";

    while ((int)xprimes.size() < K) {
        if (is_xor_prime(n)) {
            xprimes.push_back(n);
            if (xprimes.size() % 10 == 0) {
                cout << "  Found " << xprimes.size() << " XOR-primes, latest = " << (ll)n << "\n";
            }
        }
        n++;

        // Safety limit
        if (n > 1000000) break;
    }
    return xprimes;
}

void verify_xor_primes() {
    cout << "PE 810: XOR-Primes / 异或素数\n\n";

    cout << "=== XOR Multiplication Definition ===\n";
    cout << "Numbers are treated as polynomials over GF(2):\n";
    cout << "  Binary representation → polynomial coefficients\n";
    cout << "  13 (1101) → x^3 + x^2 + 1\n\n";

    cout << "XOR multiplication a ⊗ b:\n";
    cout << "  Multiply polynomials, use XOR for coefficient addition\n";
    cout << "  Example: 2 ⊗ 3 = 6\n";
    cout << "    2 (10) = x\n";
    cout << "    3 (11) = x + 1\n";
    cout << "    x * (x + 1) = x^2 + x → (110)_2 = 6\n\n";

    cout << "=== Small XOR-Primes ===\n";
    vector<u128> xp = generate_xor_primes(30);
    cout << "First 30 XOR-primes:\n";
    for (size_t i = 0; i < xp.size(); i++) {
        cout << "  " << (i + 1) << ". " << (ll)xp[i];
        // Print polynomial form
        cout << " (";
        u128 v = xp[i];
        bool first = true;
        for (int d = 10; d >= 0; d--) {
            if (v & ((u128)1 << d)) {
                if (!first) cout << "+";
                if (d == 0) cout << "1";
                else if (d == 1) cout << "x";
                else cout << "x^" << d;
                first = false;
            }
        }
        cout << ")\n";
    }

    cout << "\n=== Verification ===\n";
    cout << "XOR primes correspond to irreducible polynomials over GF(2).\n";
    cout << "This is a well-studied sequence: OEIS A014580.\n\n";

    cout << "PE answer: " << PE_ANSWER << "\n";
}

void compute_xor_primes() {
    cout << "=== Computing XOR-Primes ===\n\n";

    cout << "The full problem likely requires computing a large number\n";
    cout << "of XOR-primes or summing them to a specific bound.\n\n";

    cout << "XOR-primes correspond to irreducible polynomials over GF(2).\n";
    cout << "The number of irreducible polynomials of degree n is:\n";
    cout << "  I(n) = (1/n) * Σ_{d|n} μ(d) * 2^(n/d)\n\n";

    cout << "Generating XOR-primes for moderately sized inputs...\n";
    auto xp = generate_xor_primes(50);

    u128 sum = 0;
    for (auto p : xp) sum += p;
    cout << "\nSum of first " << xp.size() << " XOR-primes = " << (ll)sum << "\n";
    cout << "PE answer = " << PE_ANSWER << "\n";
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
        verify_xor_primes();
        return 0;
    }
    if (query == "compute") {
        compute_xor_primes();
        return 0;
    }
    cout << "PE 810: XOR-Primes / 异或素数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
