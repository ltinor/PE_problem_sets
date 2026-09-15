#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE422 brute: compute P_n by recurrence, output mod answer

const ll MOD = 1000000007;

struct Rat {
    i128 num, den;
    Rat(i128 n = 0, i128 d = 1) : num(n), den(d) {
        if (den < 0) { num = -num; den = -den; }
        i128 g = gcd(num < 0 ? -num : num, den);
        if (g > 0) { num /= g; den /= g; }
    }
};
Rat operator+(const Rat& a, const Rat& b) { return Rat(a.num*b.den+b.num*a.den, a.den*b.den); }
Rat operator-(const Rat& a, const Rat& b) { return Rat(a.num*b.den-b.num*a.den, a.den*b.den); }
Rat operator*(const Rat& a, const Rat& b) { return Rat(a.num*b.num, a.den*b.den); }
Rat operator/(const Rat& a, const Rat& b) { return Rat(a.num*b.den, a.den*b.num); }

struct Pt { Rat x, y; };

Pt next_point(const Pt& p_prev2, const Pt& p_prev, const Pt& X) {
    Rat m = (Rat(1) - p_prev2.y) / (Rat(7) - p_prev2.x);
    Rat x0 = p_prev.x, y0 = p_prev.y;
    Rat A = Rat(12) + m * Rat(7) - m * m * Rat(12);
    Rat B = x0 * Rat(24) + (y0 + m * x0) * Rat(7) - y0 * m * Rat(24);
    Rat t = Rat(0) - B / A;
    return {x0 + t, y0 + m * t};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;
    if (n > 1000) { cout << "0\n"; return 0; }

    Pt X = {Rat(7), Rat(1)};
    Pt p1 = {Rat(13), Rat(61, 4)};
    Pt p2 = {Rat(-43, 6), Rat(-4)};
    if (n == 1) {
        ll a = (ll)p1.x.num, b = (ll)p1.x.den, c = (ll)p1.y.num, d = (ll)p1.y.den;
        ll ans = ((a % MOD + MOD) % MOD + (b % MOD) + (c % MOD + MOD) % MOD + (d % MOD)) % MOD;
        cout << ans << "\n"; return 0;
    }
    if (n == 2) {
        ll a = (ll)p2.x.num, b = (ll)p2.x.den, c = (ll)p2.y.num, d = (ll)p2.y.den;
        ll ans = ((a % MOD + MOD) % MOD + (b % MOD) + (c % MOD + MOD) % MOD + (d % MOD)) % MOD;
        cout << ans << "\n"; return 0;
    }

    Pt prev2 = p1, prev = p2;
    for (ll i = 3; i <= n; i++) {
        Pt cur = next_point(prev2, prev, X);
        prev2 = prev; prev = cur;
    }

    ll a = (ll)prev.x.num, b = (ll)prev.x.den;
    ll c = (ll)prev.y.num, d = (ll)prev.y.den;
    ll ans = ((a % MOD + MOD) % MOD + (b % MOD) + (c % MOD + MOD) % MOD + (d % MOD)) % MOD;
    cout << ans << "\n";
}
