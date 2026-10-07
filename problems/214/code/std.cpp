#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 214: Totient Chains
// Original: primes < 40M, chain length 25, answer = 1677366278943
// Adapted: parameterized N, L; N ≤ 10^7, L ≤ 30

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L;
    cin >> N >> L;

    // Sieve totient
    vector<int> phi(N);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i < N; i++) {
        if (phi[i] == i) { // prime
            for (int j = i; j < N; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }

    // Compute chain lengths
    vector<int> chain_len(N, 0);
    chain_len[1] = 1;
    for (int n = 2; n < N; n++) {
        chain_len[n] = 1 + chain_len[phi[n]];
    }

    // Sum primes with chain length L
    vector<bool> is_prime(N, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    ll ans = 0;
    for (int n = 2; n < N; n++) {
        if (is_prime[n] && chain_len[n] == L) {
            ans += n;
        }
    }

    cout << ans << "\n";
}
