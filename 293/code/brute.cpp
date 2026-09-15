#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll U;
    cin >> U;

    // Brute force: enumerate all even N < U, check admissibility and compute pseudo-Fortunate
    vector<int> primes;
    for (int i = 2; i <= 100; i++) {
        bool ok = true;
        for (int j = 2; j * j <= i; j++)
            if (i % j == 0) { ok = false; break; }
        if (ok) primes.push_back(i);
    }

    set<ll> distinct_pf;

    for (ll N = 2; N < U; N += 2) {
        // Check admissibility: N is even, distinct primes are consecutive from 2
        vector<int> factors;
        ll tmp = N;
        for (int p : primes) {
            if (tmp % p == 0) {
                factors.push_back(p);
                while (tmp % p == 0) tmp /= p;
            }
        }
        if (tmp > 1) continue; // has prime factor beyond our list

        // Check consecutive
        bool ok = true;
        for (int i = 0; i < (int)factors.size(); i++) {
            if (factors[i] != primes[i]) { ok = false; break; }
        }
        if (!ok) continue;

        // Find M
        ll M = 2;
        while (!is_prime(N + M)) M++;
        distinct_pf.insert(M);
    }

    ll sum = 0;
    for (ll m : distinct_pf) sum += m;
    cout << sum << "\n";

    return 0;
}
