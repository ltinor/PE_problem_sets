#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;

// PE 234: Semidivisible numbers
// n is semidivisible if lps(n)|n xor ups(n)|n
// lps(n) = largest prime ≤ sqrt(n), ups(n) = smallest prime ≥ sqrt(n)
// Sum over n ≤ N of all semidivisible n.
// PE answer: 1259187438574927161 for N = 999966663333

// Sum of multiples of d in [L, R)
i128 sum_multiples(ll L, ll R, ll d) {
    if (d <= 0) return 0;
    ll first = (L + d - 1) / d * d; // ceil(L/d) * d
    if (first >= R) return 0;
    ll last = (R - 1) / d * d;
    if (last < first) return 0;
    ll cnt = (last - first) / d + 1;
    return (i128)cnt * (first + last) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Sieve primes up to sqrt(N) + extra margin
    ll limit = (ll)sqrt((long double)N) + 1000;
    limit = max(limit, 10LL);

    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<ll> primes;
    for (ll i = 2; i <= limit; i++) {
        if (is_prime[i]) primes.push_back(i);
    }

    i128 ans = 0;

    for (size_t k = 0; k + 1 < primes.size(); k++) {
        ll p = primes[k];
        ll q = primes[k + 1];

        ll L = p * p + 1;  // 排除 n=p²（此时 lps=ups=p，非 semidivisible）
        ll R = q * q;
        if (L > N) break;
        if (R > N + 1) R = N + 1; // [L, N] inclusive → [L, N+1)

        if (L >= R) continue;

        i128 sum_p = sum_multiples(L, R, p);
        i128 sum_q = sum_multiples(L, R, q);
        i128 sum_pq = sum_multiples(L, R, p * q);

        ans += sum_p + sum_q - 2 * sum_pq;
    }

    // Print i128
    string s;
    i128 tmp = ans;
    if (tmp == 0) s = "0";
    else {
        while (tmp > 0) {
            s += (char)('0' + (tmp % 10));
            tmp /= 10;
        }
        reverse(s.begin(), s.end());
    }
    cout << s << "\n";

    return 0;
}
