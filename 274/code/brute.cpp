#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: for each prime p, try all m from 1 to p-1
// and verify the divisibility property

ll mod_inv_brute(ll a, ll m) {
    for (ll x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return 0;
}

vector<ll> primes_up_to(ll N) {
    vector<bool> is_prime(N + 1, true);
    vector<ll> primes;
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= N; j += i)
                is_prime[j] = false;
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll limit;
    cin >> limit;

    auto primes = primes_up_to(limit);
    ll sum = 0;

    for (ll p : primes) {
        if (p == 2 || p == 5) continue;
        ll m = mod_inv_brute(10, p);
        sum += m;
    }

    cout << sum << "\n";
    return 0;
}
