#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE347 brute: same as std, enumerate prime pairs
vector<ll> primes;
vector<bool> is_prime;

void sieve(ll n) {
    is_prime.assign(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i*i; j <= n; j += i) is_prime[j] = false;
        }
    }
}

int main() {
    ll N; cin >> N;
    sieve(N/2 + 5);

    unordered_set<ll> values;
    for (size_t a = 0; a < primes.size(); a++) {
        ll p = primes[a];
        if (p > N/2) break;
        for (size_t b = a+1; b < primes.size(); b++) {
            ll q = primes[b];
            if (p * q > N) break;
            ll best = 0;
            for (ll pi = p; pi <= N/q; pi *= p) {
                ll lim = N / pi;
                for (ll qj = q; qj <= lim; qj *= q) {
                    ll val = pi * qj;
                    if (val > best) best = val;
                }
            }
            if (best > 0) values.insert(best);
        }
    }

    ll ans = 0;
    for (ll x : values) ans += x;
    cout << ans << "\n";
}
