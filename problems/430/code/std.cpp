#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE430: Range flips
// N disks, M turns. E(N,M) = expected white disks.
// For disk i: p_i = P(flipped in one turn) = (2*i*(N-i+1) - 1) / N^2
// P(white after M turns) = (1 + (1-2p_i)^M) / 2
// E = N/2 + (1/2) * sum_{i=1}^{N} (1-2p_i)^M

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    ll N, M;
    cin >> N >> M;
    
    // Use symmetry: only compute for i=1..N/2, double it
    // For N even, no middle term. For N odd, handle middle separately.
    
    long double sum = 0.0L;
    long double N2 = (long double)N * N;
    
    // We only need to sum terms where |1-2p_i|^M is not negligible
    // For large N, p_i ≈ 2i/N for small i
    // |1-2p_i|^M = (1-4i/N)^M ≈ exp(-4Mi/N)
    // Cutoff when exp(-4Mi/N) < 1e-20 → 4Mi/N > 46 → i > 11.5*N/M
    ll limit = min(N/2, (ll)(12.0 * N / M + 1000000));
    if (limit > N/2) limit = N/2;
    
    for (ll i = 1; i <= limit; i++) {
        long double p = (2.0L * i * (N - i + 1) - 1.0L) / N2;
        long double base = 1.0L - 2.0L * p; // 1 - 2p_i
        // base is close to 1 for small i
        long double term = powl(fabsl(base), (long double)M);
        if (base < 0 && (M % 2 == 1)) term = -term;
        sum += term;
    }
    
    // Double for symmetry (i and N-i+1 are symmetric)
    sum *= 2.0L;
    
    // Add middle term if N is odd
    if (N % 2 == 1 && limit >= (N+1)/2) {
        // Already counted twice, subtract one copy
        ll mid = (N + 1) / 2;
        long double p_mid = (2.0L * mid * (N - mid + 1) - 1.0L) / N2;
        long double base_mid = 1.0L - 2.0L * p_mid;
        long double term_mid = powl(fabsl(base_mid), (long double)M);
        if (base_mid < 0 && (M % 2 == 1)) term_mid = -term_mid;
        sum -= term_mid;
    }
    
    long double ans = N / 2.0L + sum / 2.0L;
    
    cout << fixed << setprecision(2) << ans << "\n";
    return 0;
}
