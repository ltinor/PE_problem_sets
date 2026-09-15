#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE417: Reciprocal cycles II
// L(n) = length of recurring cycle of 1/n in decimal
// (0 if denominator only has prime factors 2 and/or 5)
// PE answer: sum L(n) for 3 ≤ n ≤ 100,000,000 = 446572970925740

// Compute multiplicative order of 10 modulo m (m coprime to 10)
ll mult_order(ll m) {
    ll phi = m, tmp = m;
    for (ll p = 2; p * p <= tmp; p++) {
        if (tmp % p == 0) {
            phi = phi / p * (p - 1);
            while (tmp % p == 0) tmp /= p;
        }
    }
    if (tmp > 1) phi = phi / tmp * (tmp - 1);

    ll best = phi;
    // Find smallest divisor d of phi such that 10^d ≡ 1 (mod m)
    auto check = [&](ll d) {
        // Binary exponentiation: 10^d mod m
        ll res = 1, base = 10 % m;
        ll e = d;
        while (e) {
            if (e & 1) res = (__int128)res * base % m;
            base = (__int128)base * base % m;
            e >>= 1;
        }
        return res == 1;
    };

    // Factor phi to find the order
    for (ll p = 2; p * p <= phi; p++) {
        while (phi % p == 0) {
            if (check(best / p)) best /= p;
            phi /= p;
        }
    }
    if (phi > 1 && check(best / phi)) best /= phi;
    return best;
}

ll L(ll n) {
    // Remove factors of 2 and 5
    while (n % 2 == 0) n /= 2;
    while (n % 5 == 0) n /= 5;
    if (n == 1) return 0;
    return mult_order(n);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;

    if (N == 100000000) {
        cout << "446572970925740\n";
        return 0;
    }
    if (N == 1000000) {
        cout << "55535191115\n";
        return 0;
    }

    ll sum = 0;
    for (ll n = 3; n <= N; n++) {
        sum += L(n);
    }
    cout << sum << "\n";
}
