#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd3(ll a, ll b, ll c) {
    return std::gcd((unsigned long long)a,
           std::gcd((unsigned long long)b, (unsigned long long)c));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    set<tuple<ll, ll, ll>> primitives;

    // Equilateral (1,1,1) — special case not covered by parametrizations
    primitives.insert({1, 1, 1});

    // -------------------------------------------------------
    // 1. Pythagorean (90°)
    // -------------------------------------------------------
    for (ll m = 2; ; m++) {
        if (2 * m * (m + 1) > N) break;
        for (ll n = 1; n < m; n++) {
            if ((m - n) % 2 == 0) continue;
            if (std::gcd((unsigned long long)m, (unsigned long long)n) != 1) continue;
            ll P = 2 * m * (m + n);
            if (P > N) break;
            ll a = m * m - n * n;
            ll b = 2 * m * n;
            ll c = m * m + n * n;
            vector<ll> s = {a, b, c};
            sort(s.begin(), s.end());
            primitives.insert({s[0], s[1], s[2]});
        }
    }

    // -------------------------------------------------------
    // 2. 60°  (a² + b² - ab = c²)
    //
    // In Z[ω], primitive solutions: a + bω = u · (x + yω)²
    // where u ∈ {1, ω, ω²} (units with non-negative norm).
    //
    // Form 1 (u=1):  a = x² - y²,            b = 2xy - y²
    // Form 2 (u=ω):  a = |y² - 2xy|,         b = |x² - 2xy|
    // Form 3 (u=ω²): a = |2xy - x²|,         b = x² - y²
    //
    // In all cases c = x² - xy + y².
    // We must verify a²+b²-ab == c² because absolute values may break it.
    // -------------------------------------------------------
    for (ll x = 2; ; x++) {
        // c = x² - x·1 + 1 = x² - x + 1   (minimum c for given x)
        if (x * x - x + 1 > N) break;
        for (ll y = 1; y < x; y++) {
            if (std::gcd((unsigned long long)x, (unsigned long long)y) != 1) continue;
            if ((x - y) % 3 == 0) continue;

            ll c = x * x - x * y + y * y;
            if (c > N) continue;

            // Form 1
            {
                ll a = x * x - y * y;
                ll b = 2 * x * y - y * y;
                if (a > 0 && b > 0 && a * a + b * b - a * b == c * c && gcd3(a, b, c) == 1) {
                    ll P = a + b + c;
                    if (P <= N) {
                        vector<ll> s = {a, b, c};
                        sort(s.begin(), s.end());
                        primitives.insert({s[0], s[1], s[2]});
                    }
                }
            }
            // Form 2
            {
                ll a = llabs(y * y - 2 * x * y);
                ll b = llabs(x * x - 2 * x * y);
                if (a > 0 && b > 0 && a * a + b * b - a * b == c * c && gcd3(a, b, c) == 1) {
                    ll P = a + b + c;
                    if (P <= N) {
                        vector<ll> s = {a, b, c};
                        sort(s.begin(), s.end());
                        primitives.insert({s[0], s[1], s[2]});
                    }
                }
            }
            // Form 3
            {
                ll a = llabs(2 * x * y - x * x);
                ll b = x * x - y * y;
                if (a > 0 && b > 0 && a * a + b * b - a * b == c * c && gcd3(a, b, c) == 1) {
                    ll P = a + b + c;
                    if (P <= N) {
                        vector<ll> s = {a, b, c};
                        sort(s.begin(), s.end());
                        primitives.insert({s[0], s[1], s[2]});
                    }
                }
            }
        }
    }

    // -------------------------------------------------------
    // 3. 120°  (a² + b² + ab = c²)
    //
    // Primitive: a = x² - y²,  b = 2xy + y²,  c = x² + xy + y²
    // -------------------------------------------------------
    for (ll x = 2; ; x++) {
        if ((2 * x + 1) * (x + 1) > N) break;
        for (ll y = 1; y < x; y++) {
            if (std::gcd((unsigned long long)x, (unsigned long long)y) != 1) continue;
            if ((x - y) % 3 == 0) continue;
            ll a = x * x - y * y;
            ll b = 2 * x * y + y * y;
            ll c = x * x + x * y + y * y;
            if (a <= 0 || b <= 0) continue;
            ll P = a + b + c;
            if (P > N) break;
            if (gcd3(a, b, c) != 1) continue;
            vector<ll> s = {a, b, c};
            sort(s.begin(), s.end());
            primitives.insert({s[0], s[1], s[2]});
        }
    }

    ll ans = 0;
    for (auto [a, b, c] : primitives) {
        ll P = a + b + c;
        ans += N / P;
    }

    cout << ans << "\n";
    return 0;
}
