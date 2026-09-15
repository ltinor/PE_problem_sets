#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Count numbers < N with exactly 2 prime factors (semiprimes)
// For each prime p, count primes q such that p <= q and p*q < N

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Simple sieve to get all primes < N
    vector<bool> is_prime(N, true);
    vector<ll> primes;
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    ll ans = 0;
    int sz = primes.size();
    for (int i = 0; i < sz; i++) {
        ll p = primes[i];
        if (p * p >= N) break;
        // Find largest q such that p * q < N
        // Use binary search or linear scan
        for (int j = i; j < sz; j++) {
            ll q = primes[j];
            if (p * q < N) {
                ans++;
            } else {
                break;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
