#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// PE403 brute: compute S(N) via enumeration
// Check if a^2+4b is perfect square, then count lattice points

bool is_square(ll x) {
    if (x < 0) return false;
    ll r = (ll)sqrt((long double)x);
    while (r * r < x) ++r;
    while (r * r > x) --r;
    return r * r == x;
}

ll count_lattice_points(ll a, ll b) {
    ll disc = a * a + 4 * b;
    if (disc < 0 || !is_square(disc)) return 0;
    ll k = (ll)sqrt((long double)disc);
    auto ceil_div = [](ll num, ll den) -> ll {
        if (num >= 0) return (num + den - 1) / den;
        else return num / den;
    };
    auto floor_div = [](ll num, ll den) -> ll {
        if (num >= 0) return num / den;
        else return (num - den + 1) / den;
    };
    ll x_lo = ceil_div(a - k, 2);
    ll x_hi = floor_div(a + k, 2);
    ll cnt = 0;
    for (ll x = x_lo; x <= x_hi; ++x) {
        ll y_lo = x * x;
        ll y_hi = a * x + b;
        if (y_lo <= y_hi)
            cnt += y_hi - y_lo + 1;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    const ll MOD = 100000000;
    ll total = 0;
    for (ll a = -N; a <= N; ++a)
        for (ll b = -N; b <= N; ++b)
            if (is_square(a * a + 4 * b))
                total = (total + count_lattice_points(a, b)) % MOD;
    cout << total << "\n";
}
