#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 1000000000000000000LL; // 10^18

// Brute force: directly search for smallest n!

ll fact_vp(ll n, ll p) {
    ll cnt = 0;
    while (n > 0) {
        n /= p;
        cnt += n;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll U, K;
    cin >> U >> K;

    // Generate small primes
    vector<ll> primes;
    for (ll p = 2; p <= U; p++) {
        bool is_p = true;
        for (ll d = 2; d * d <= p; d++) {
            if (p % d == 0) { is_p = false; break; }
        }
        if (is_p) primes.push_back(p);
    }

    ll sum = 0;
    for (ll i = 10; i <= U; i++) {
        ll Ni = 0;
        for (ll p : primes) {
            if (p > i) break;

            // v_p(i!)
            ll vi = 0;
            ll temp = i;
            while (temp > 0) { temp /= p; vi += temp; }

            if (vi == 0) continue;

            ll target = K * vi;

            // Linear search
            for (ll n = 1; ; n++) {
                if (fact_vp(n, p) >= target) {
                    Ni = max(Ni, n);
                    break;
                }
            }
        }
        sum = (sum + Ni) % MOD;
    }

    cout << sum << "\n";
    return 0;
}
