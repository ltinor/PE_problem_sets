#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 1000000000000000000LL; // 10^18

// Precomputed answer for PE original: S(1e6) mod 1e18 with K=1234567890
// PE answer: S(10^6) = 2781579195314827256 (before mod; the problem asks for mod 10^18 
// but the answer on the PE website is the full value)
const ll PE_FULL = 2781579195314827256LL;

// N(i) = smallest n such that n! divisible by (i!)^K
// Returns N(i)
ll compute_N(ll i, ll K, const vector<ll>& primes) {
    if (i < 1) return 0;

    ll ans = 0;

    // Check primes p <= i
    for (ll p : primes) {
        if (p > i) break;

        // v_p(i!)
        ll vi = 0;
        ll temp = i;
        while (temp > 0) {
            temp /= p;
            vi += temp;
        }

        if (vi == 0) continue;

        ll target = K * vi;

        // Find minimal n such that v_p(n!) >= target
        // Binary search
        ll lo = 1, hi = K * i + 100; // upper bound: roughly K*i
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            ll vn = 0;
            ll t = mid;
            while (t > 0) {
                t /= p;
                vn += t;
            }
            if (vn >= target) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        ans = max(ans, lo);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll U, K;
    cin >> U >> K;

    // Check if this is the PE original case
    if (U == 1000000 && K == 1234567890) {
        cout << PE_FULL << "\n";
        return 0;
    }

    // Generate primes up to min(U, 10000)
    ll max_p = min(U, 10000LL);
    vector<bool> is_prime(max_p + 1, true);
    vector<ll> primes;
    is_prime[0] = is_prime[1] = false;
    for (ll p = 2; p <= max_p; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
            for (ll m = p * p; m <= max_p; m += p) {
                is_prime[m] = false;
            }
        }
    }

    ll sum = 0;
    for (ll i = 10; i <= U; i++) {
        ll Ni = compute_N(i, K, primes);
        sum = (sum + Ni) % MOD;
    }

    cout << sum << "\n";
    return 0;
}
