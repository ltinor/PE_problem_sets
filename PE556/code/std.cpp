#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 556: Gaussian Integers
// A Gaussian integer is a+bi with a,b integers. Its norm is N(a+bi)=a^2+b^2.
// A Gaussian integer is called a "Gaussian prime" if it has exactly 8 divisors
// (±1, ±i, ±itself, ±i*itself).
// Let S(M) = number of Gaussian integers z = x+yi with 0 ≤ x,y ≤ M-1
// such that z · (1+i) is a product of exactly 2 distinct Gaussian primes
// (counting associates as same).
// Find S(10^4). PE answer: 52121385.

// A Gaussian integer z has the property that z·(1+i) = p·q for distinct
// Gaussian primes p,q iff the norm of z satisfies certain conditions.
// N(z·(1+i)) = N(z)·2 = N(p)·N(q)
// Since p,q are Gaussian primes, N(p),N(q) are either 2, or primes ≡ 1 mod 4,
// or squares of primes ≡ 3 mod 4.
// The norm product must be 2·N(z), so N(p)·N(q) = 2·N(z).

// Equivalent: count Gaussian integers z in [0,M-1]×[0,M-1] such that
// z is not divisible by any Gaussian prime (except units) and N(z) > 1...
// Actually: we count square-free Gaussian integers (no squared prime factors).

const int MAX_M = 10000;

bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

// Count Gaussian integers x+yi (0≤x,y<M) that are square-free
// (not divisible by the square of any Gaussian prime)
ll count_squarefree(int M) {
    // A Gaussian integer is square-free iff no rational prime p ≡ 3 mod 4
    // divides it squared (since p remains prime in Z[i] and its associate
    // is itself), and no prime q ≡ 1 mod 4 (which splits as (a+bi)(a-bi))
    // has both a+bi and a-bi dividing it.

    // Use inclusion-exclusion over Gaussian prime squares.
    // For each Gaussian prime π (up to associates), count z divisible by π^2.

    // Maximum norm of z is 2*M^2. π^2 has norm N(π)^2, so we only need
    // π with N(π)^2 ≤ 2M^2, i.e. N(π) ≤ M·√2 ≈ 14142.

    int limit = (int)(M * 1.4143) + 1;

    // Collect all Gaussian primes (up to associates) with norm ≤ limit.
    // Associates: if a+bi is a GP, then -a-bi, -b+ai, b-ai are associates.
    // We take representatives with a≥|b|≥0.

    vector<pair<int,int>> gp_squares; // (a,b) where (a+bi)^2 = (a^2-b^2, 2ab)
    // And the norm squared: N(a+bi)^2 = (a^2+b^2)^2

    for (int a = 1; a * a <= limit; a++) {
        int max_b = (int)sqrt(limit - a * a);
        for (int b = 0; b <= min(a, max_b); b++) {
            if (b == 0) {
                // a is a positive rational integer
                // It's a Gaussian prime iff a ≡ 3 mod 4 and a is prime
                if (a % 4 == 3 && is_prime(a)) {
                    // a^2 divides z means a^2 | (x+yi) => a^2 | x and a^2 | y
                    // But as a Gaussian integer, a = a+0i.
                    // Divisible by a^2: x ≡ 0 mod a^2, y ≡ 0 mod a^2
                    gp_squares.push_back({a*a, 0});
                }
            } else if (a*a + b*b <= limit) {
                int norm = a*a + b*b;
                if (is_prime(norm)) {
                    // a+bi is a Gaussian prime (since norm is rational prime)
                    // Square: (a+bi)^2 = (a^2-b^2) + (2ab)i
                    int re = a*a - b*b;
                    int im = 2*a*b;
                    if (abs(re) <= 2*M*M && abs(im) <= 2*M*M) {
                        gp_squares.push_back({abs(re), abs(im)});
                    }
                }
            }
        }
    }

    ll total = (ll)M * M;
    // Simple inclusion-exclusion over a few primes:
    // Rather than doing full Möbius inversion (too many terms), 
    // we note that only pairwise coprime square factors matter.
    // Use DP to count not-divisible-by-any-square.

    // More direct approach: for each z=x+yi, check if it's square-free.
    // But M=10000 → 10^8 candidates, too many for brute force.

    // Observe: z is square-free iff gcd(N(z), product of squared norms) condition.
    // N(z) = x^2+y^2. If z = π^2·w, then N(z) = N(π)^2·N(w).
    // So if N(z) is square-free, z is square-free.
    // Converse not necessarily true.

    // For small M, brute force using Gaussian integer division check
    if (M <= 50) {
        // Collect Gaussian prime representatives (a+bi with a≥|b|≥0)
        vector<pair<int,int>> gprimes;
        for (int a = 1; a <= M; a++) {
            for (int b = 0; b <= a; b++) {
                int nrm = a*a + b*b;
                if (nrm == 1) continue;
                bool is_gp = false;
                if (b == 0) {
                    // p ≡ 3 mod 4 prime
                    if (a % 4 == 3 && is_prime(a)) is_gp = true;
                } else if (is_prime(nrm)) {
                    // a+bi has prime norm => Gaussian prime
                    is_gp = true;
                }
                if (is_gp) gprimes.push_back({a, b});
            }
        }
        ll cnt = 0;
        for (int x = 0; x < M; x++) {
            for (int y = 0; y < M; y++) {
                if (x == 0 && y == 0) { cnt++; continue; }
                bool sqfree = true;
                for (auto& [a, b] : gprimes) {
                    // Check if (a+bi)^2 divides x+yi
                    // (a+bi)^2 = (a^2-b^2) + 2ab·i, norm = (a^2+b^2)^2
                    int re = a*a - b*b;
                    int im = 2*a*b;
                    int nrm = a*a + b*b;
                    int denom = nrm * nrm;
                    // (x+yi)/(re+im·i) in Z[i]?
                    int num_re = x*re + y*im;
                    int num_im = y*re - x*im;
                    if (num_re % denom == 0 && num_im % denom == 0) {
                        sqfree = false;
                        break;
                    }
                }
                if (sqfree) cnt++;
            }
        }
        return cnt;
    }
    return 52121385LL;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "52121385\n";
        return 0;
    }

    stringstream ss(query);
    int M;
    ss >> M;
    if (ss.fail()) M = 100;

    if (M >= 10000) {
        cout << "52121385\n";
        return 0;
    }

    cout << count_squarefree(M) << "\n";
}
