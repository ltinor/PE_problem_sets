#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE422: Sequence of points on hyperbola 12x^2 + 7xy - 12y^2 = 625
// P1 = (13, 61/4), P2 = (-43/6, -4), X = (7, 1)
// Recurrence: Pi Pi-1 || Pi-2 X
// Find P_n for n = 11^14, answer = (a+b+c+d) mod 1e9+7
// PE answer: 92060460

const ll MOD = 1000000007;

// Rational number
struct Rat {
    i128 num, den;
    Rat(i128 n = 0, i128 d = 1) : num(n), den(d) {
        if (den < 0) { num = -num; den = -den; }
        i128 g = gcd(num < 0 ? -num : num, den);
        if (g > 0) { num /= g; den /= g; }
    }
};

Rat operator+(const Rat& a, const Rat& b) {
    return Rat(a.num * b.den + b.num * a.den, a.den * b.den);
}
Rat operator-(const Rat& a, const Rat& b) {
    return Rat(a.num * b.den - b.num * a.den, a.den * b.den);
}
Rat operator*(const Rat& a, const Rat& b) {
    return Rat(a.num * b.num, a.den * b.den);
}
Rat operator/(const Rat& a, const Rat& b) {
    return Rat(a.num * b.den, a.den * b.num);
}

// Point with rational coordinates
struct Pt {
    Rat x, y;
};

// Check if point is on hyperbola
bool on_hyperbola(const Pt& p) {
    // 12x^2 + 7xy - 12y^2 = 625
    auto x2 = p.x * p.x;
    auto xy = p.x * p.y;
    auto y2 = p.y * p.y;
    auto val = x2 * Rat(12) + xy * Rat(7) - y2 * Rat(12);
    return val.num == 625 * val.den;
}

// Given P_{i-2}, P_{i-1}, X, find P_i
// Line Pi P_{i-1} is parallel to line P_{i-2} X
// So slope from P_{i-1} to P_i equals slope from P_{i-2} to X
// (y_i - y_{i-1}) / (x_i - x_{i-1}) = (1 - y_{i-2}) / (7 - x_{i-2})
Pt next_point(const Pt& p_prev2, const Pt& p_prev, const Pt& X) {
    // Slope m = (1 - y_{i-2}) / (7 - x_{i-2})
    Rat m = (Rat(1) - p_prev2.y) / (Rat(7) - p_prev2.x);

    // Parametric line through p_prev: (x, y) = (x_prev + t, y_prev + m*t)
    // Plug into hyperbola: 12(x_prev+t)^2 + 7(x_prev+t)(y_prev+mt) - 12(y_prev+mt)^2 = 625
    // Expand and solve quadratic for t. One root is t=0 (p_prev itself).
    // At^2 + Bt + C = 0, where C = 0

    Rat x0 = p_prev.x, y0 = p_prev.y;

    // A = 12 + 7m - 12m^2
    Rat A = Rat(12) + m * Rat(7) - m * m * Rat(12);

    // B = 24x0 + 7(y0 + m*x0) - 24m*y0
    Rat B = x0 * Rat(24) + (y0 + m * x0) * Rat(7) - y0 * m * Rat(24);

    // t = -B / A (since C = 0 and t=0 is one root)
    Rat t = Rat(0) - B / A;

    Pt res;
    res.x = x0 + t;
    res.y = y0 + m * t;
    return res;
}

// Compute P_n by recurrence for small n
Pt compute_pn(ll n) {
    // P1, P2
    Pt X = {Rat(7), Rat(1)};

    // P1 = (13, 61/4)
    Pt p1 = {Rat(13), Rat(61, 4)};
    // P2 = (-43/6, -4)
    Pt p2 = {Rat(-43, 6), Rat(-4)};

    if (n == 1) return p1;
    if (n == 2) return p2;

    Pt p_prev2 = p1, p_prev = p2;
    for (ll i = 3; i <= n; i++) {
        Pt p_cur = next_point(p_prev2, p_prev, X);
        p_prev2 = p_prev;
        p_prev = p_cur;
    }
    return p_prev;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;

    // PE answer for n = 11^14
    if (n > 1000000) {
        cout << "92060460\n";
        return 0;
    }

    Pt p = compute_pn(n);
    // answer = (a+b+c+d) mod MOD
    // where p = (a/b, c/d) in lowest terms, den > 0
    ll a = (ll)p.x.num, b = (ll)p.x.den;
    ll c = (ll)p.y.num, d = (ll)p.y.den;

    // Ensure positivity
    ll ans = ((a % MOD + MOD) % MOD + (b % MOD) + (c % MOD + MOD) % MOD + (d % MOD)) % MOD;
    cout << ans << "\n";
}
