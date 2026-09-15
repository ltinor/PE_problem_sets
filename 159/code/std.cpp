#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 159: Digital Root Sums
// Parameterized: input N (< 10^6), output sum of mdrs(n) for 2..N
// mdrs(n) = max over factorizations of digital root sums

// Digital root
int dr(ll n) {
    if (n == 0) return 0;
    return 1 + (n - 1) % 9;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // mdrs[i] for i = 2..N
    vector<int> mdrs(N + 1, 0);

    ll total = 0;

    for (int i = 2; i <= N; i++) {
        // Start with digital root of i itself (no factorization)
        int best = dr(i);

        // Try factorizations: for each divisor d of i
        // mdrs(i) = max(dr(d) + mdrs(i/d))
        // Only need to check d up to sqrt(i)
        for (int d = 2; d * d <= i; d++) {
            if (i % d == 0) {
                int d2 = i / d;
                best = max(best, dr(d) + mdrs[d2]);
                best = max(best, dr(d2) + mdrs[d]);
            }
        }

        mdrs[i] = best;
        total += best;
    }

    cout << total << "\n";
    return 0;
}
