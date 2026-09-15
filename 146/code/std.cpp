#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Miller-Rabin deterministic for 64-bit
ll mul_mod(ll a, ll b, ll m) {
    return (__int128)a * b % m;
}

ll pow_mod(ll a, ll n, ll m) {
    ll r = 1;
    a %= m;
    while (n) {
        if (n & 1) r = mul_mod(r, a, m);
        a = mul_mod(a, a, m);
        n >>= 1;
    }
    return r;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }

    // bases for 64-bit deterministic Miller-Rabin
    ll bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ll a : bases) {
        if (a >= n) continue;
        ll x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// Check if [n²+1, n²+3, n²+7, n²+9, n²+13, n²+27] are consecutive primes
bool check(ll n) {
    if (n % 10 != 0) return false;
    if (n % 3 == 0) return false;
    if (n % 7 != 3 && n % 7 != 4) return false;

    ll n2 = n * n;

    // All 6 target numbers must be prime
    if (!is_prime(n2 + 1)) return false;
    if (!is_prime(n2 + 3)) return false;
    if (!is_prime(n2 + 7)) return false;
    if (!is_prime(n2 + 9)) return false;
    if (!is_prime(n2 + 13)) return false;
    if (!is_prime(n2 + 27)) return false;

    // Gap numbers must be composite
    ll gaps[] = {5, 11, 15, 17, 19, 21, 23, 25};
    for (ll g : gaps) {
        if (is_prime(n2 + g)) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    ll ans = 0;
    // n must be divisible by 10, and n%3!=0, n%7∈{3,4}
    for (ll n = 10; n < M; n += 10) {
        if (n % 3 == 0) continue;
        ll r7 = n % 7;
        if (r7 != 3 && r7 != 4) continue;
        if (check(n)) {
            ans += n;
        }
    }

    cout << ans << "\n";
    return 0;
}
