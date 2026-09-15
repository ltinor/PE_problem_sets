#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Extended Euclidean
ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll g = egcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

// CRT: returns (lcm, rem) where x ≡ rem (mod lcm), or (-1,-1)
pair<ll, ll> crt(ll r1, ll m1, ll r2, ll m2) {
    ll g = std::gcd((unsigned long long)m1, (unsigned long long)m2);
    if ((r2 - r1) % g != 0) return {-1, -1};
    ll l = m1 / g * m2;
    ll x, y;
    egcd(m1 / g, m2 / g, x, y);
    ll r = r1 + m1 * x * ((r2 - r1) / g);
    r = (r % l + l) % l;
    return {l, r};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    ll T;
    cin >> S >> T;

    // Work backwards through the sequence S.
    // We maintain: a_1 ≡ R (mod M) for the first k steps of S (processed from end).
    // Initially no constraint: a_{m+1} can be anything.
    ll M = 1, R = 0;

    for (int i = (int)S.size() - 1; i >= 0; i--) {
        char op = S[i];
        if (op == 'D') {
            // a_i = 3 * a_{i+1}. a_i ≡ 0 (mod 3) automatically.
            // Given a_{i+1} ≡ R (mod M), a_i ≡ 3R (mod 3M).
            R = 3 * R;
            M = 3 * M;
        } else if (op == 'U') {
            // a_i = (3*a_{i+1} - 2) / 4, need a_{i+1} ≡ 2 (mod 4)
            auto [lm, rr] = crt(R, M, 2, 4);
            if (lm == -1) { cerr << "No solution for U\n"; return 1; }
            M = lm; R = rr;
            // Now a_i = (3*R' - 2) / 4, new stride = 3*M/4
            R = (3 * R - 2) / 4;
            M = 3 * M / 4;
        } else { // 'd'
            // a_i = (3*a_{i+1} + 1) / 2, need a_{i+1} odd
            auto [lm, rr] = crt(R, M, 1, 2);
            if (lm == -1) { cerr << "No solution for d\n"; return 1; }
            M = lm; R = rr;
            R = (3 * R + 1) / 2;
            M = 3 * M / 2;
        }
        R = (R % M + M) % M;
    }

    // a_1 ≡ R (mod M), find smallest > T
    ll a1 = R;
    if (a1 <= T) {
        ll k = (T - a1) / M + 1;
        a1 = a1 + k * M;
    }

    cout << a1 << "\n";
    return 0;
}
