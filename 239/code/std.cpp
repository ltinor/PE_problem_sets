#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 239: Twenty-two Foolish Primes
// N disks numbered 1..N. K prime disks exactly displaced.
// Output probability rounded to 12 decimal places (0.abcdefghijkl)

// Number of primes <= N: let P = count primes in [1, N].
// We need: choose which C(P, P-K) primes stay in place.
// The K displaced primes must all move from their spots.
// The N-P non-primes can be anywhere.
// 
// Total = C(P, P-K) * D where D = number of permutations where
// the K specific primes avoid their original positions.
//
// Inclusion-exclusion for K specific primes:
// D = sum_{j=0}^{K} (-1)^j * C(K, j) * (N - j)!
//
// Total valid = C(P, P-K) * sum_{j=0}^{K} (-1)^j * C(K, j) * (N - j)!
// Probability = Total valid / N!

// Use long double for computation

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    // Count primes <= N
    int P = 0;
    for (int i = 2; i <= N; i++)
        if (is_prime(i)) P++;

    if (K > P) {
        cout << "0.000000000000\n";
        return 0;
    }

    // Compute probability using long double
    // F = P - K primes stay fixed
    // prob = C(P, F) * sum_{j=0}^{K} (-1)^j * C(K, j) * (N - F - j)! / N!
    //      = C(P, F) * sum_{j=0}^{K} (-1)^j * C(K, j) / prod_{t=0}^{F+j-1} (N - t)

    int F = P - K; // number of fixed primes

    long double prob = 0.0L;

    // Compute C(P, F)
    long double C_P_F = 1.0L;
    for (int i = 0; i < F; i++) {
        C_P_F = C_P_F * (P - i) / (i + 1);
    }

    for (int j = 0; j <= K; j++) {
        // C(K, j)
        long double C_K_j = 1.0L;
        for (int i = 0; i < j; i++) {
            C_K_j = C_K_j * (K - i) / (i + 1);
        }

        // denominator = N * (N-1) * ... * (N - F - j + 1)
        // product of (F + j) terms
        long double denom = 1.0L;
        for (int t = 0; t < F + j; t++) {
            denom *= (N - t);
        }

        long double term = C_K_j / denom;
        if (j % 2 == 1) term = -term;
        prob += term;
    }

    prob *= C_P_F;

    // Output rounded to 12 decimal places
    cout << fixed << setprecision(12) << prob << "\n";

    return 0;
}
