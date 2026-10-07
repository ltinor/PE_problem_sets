#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd_ll(ll a, ll b) { while (b) { ll t = a % b; a = b; b = t; } return a; }

// ============================================================================
// PE 964: Musical Chairs Revisited / 变种音乐椅游戏
//
// k(k-1)/2 + 1 children play k rounds.  Round i (1-indexed) selects i random
// children (all combinations equally likely) and then seats them back randomly
// among the i vacated chairs (all permutations equally likely).
//
// P(k) = probability that after all k rounds every child is exactly one chair
// to the right of their original chair.
//
// Given: P(3) = 1/72 = 1.3888888889e-2.  This program reads k and prints P(k)
// in scientific notation with 10 significant digits.
//
// ----------------------------------------------------------------------------
// Algorithm (representation theory of the symmetric group S_T, T=k(k-1)/2+1):
//
// In each round the chair permutation is a "random i-subset permutation" with
// distribution f_i (a class function on S_T).  The final permutation is the
// product of these k random permutations, so
//      P(k) = (f_1 * f_2 * ... * f_k)(s),   s = the full T-cycle.
//
// Fourier inversion over the irreducible representations gives
//      P(k) = (1/T!) * sum_{lambda |- T} d_lambda * chi_lambda(s)
//                          * prod_{i=1..k} omega_i(lambda),
// where omega_i(lambda) = (1/d_lambda) * sum_g f_i(g) chi_lambda(g).
//
// By Murnaghan-Nakayama, chi_lambda(s) is non-zero only when lambda is a hook
// lambda = (a, 1^{T-a}); for such a hook chi = (-1)^{T-a} and d = C(T-1,a-1).
// For a hook, omega_i = m_i / d where m_i is the multiplicity of the trivial
// S_i-representation in the restriction of the hook irrep, i.e. the sum of
// dimensions f^mu over partitions mu obtained from lambda by removing a
// horizontal strip of i boxes.  This gives the closed form used below.
// ============================================================================

// ---- minimal big unsigned integer (base 1e9, little endian) ---------------
struct BigInt {
    static constexpr ll BASE = 1000000000LL;
    vector<ll> d; // each in [0, BASE)

    BigInt() = default;
    BigInt(ll v) { while (v > 0) { d.push_back(v % BASE); v /= BASE; } }

    bool isZero() const { return d.empty(); }
    void trim() { while (!d.empty() && d.back() == 0) d.pop_back(); }

    static BigInt add(const BigInt& a, const BigInt& b) {
        BigInt r; ll carry = 0;
        size_t n = max(a.d.size(), b.d.size());
        for (size_t i = 0; i < n; ++i) {
            ll s = carry;
            if (i < a.d.size()) s += a.d[i];
            if (i < b.d.size()) s += b.d[i];
            if (s >= BASE) { s -= BASE; carry = 1; } else carry = 0;
            r.d.push_back(s);
        }
        if (carry) r.d.push_back(carry);
        return r;
    }

    // a - b, requires a >= b
    static BigInt sub(const BigInt& a, const BigInt& b) {
        BigInt r; ll borrow = 0;
        for (size_t i = 0; i < a.d.size(); ++i) {
            ll s = a.d[i] - borrow;
            if (i < b.d.size()) s -= b.d[i];
            if (s < 0) { s += BASE; borrow = 1; } else borrow = 0;
            r.d.push_back(s);
        }
        r.trim();
        return r;
    }

    // a * x  (x < BASE)
    static BigInt mulSmall(const BigInt& a, ll x) {
        if (x == 0 || a.isZero()) return BigInt();
        BigInt r; ll carry = 0;
        for (size_t i = 0; i < a.d.size(); ++i) {
            ll cur = a.d[i] * x + carry;
            r.d.push_back(cur % BASE);
            carry = cur / BASE;
        }
        while (carry > 0) { r.d.push_back(carry % BASE); carry /= BASE; }
        return r;
    }

    static int cmp(const BigInt& a, const BigInt& b) {
        if (a.d.size() != b.d.size()) return a.d.size() < b.d.size() ? -1 : 1;
        for (int i = (int)a.d.size() - 1; i >= 0; --i)
            if (a.d[i] != b.d[i]) return a.d[i] < b.d[i] ? -1 : 1;
        return 0;
    }

    // convert to long double (only used for the final division; the sum is
    // computed exactly above so no cancellation happens here).
    long double to_ld() const {
        long double r = 0.0L;
        for (int i = (int)d.size() - 1; i >= 0; --i)
            r = r * (long double)BASE + (long double)d[i];
        return r;
    }
};

// binomial C(n, r) for small n (n <= T <= 22 here)
ll binom(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    r = min(r, n - r);
    ll res = 1;
    for (ll i = 1; i <= r; ++i) res = res * (n - r + i) / i;
    return res;
}

// dimension of the hook partition (c, 1^r)  == C(c+r-1, r)
ll fhook(ll c, ll r) { return binom(c + r - 1, r); }

// multiplicity of the trivial S_i-representation in the hook irrep (a, 1^b)
ll multiplicity(ll a, ll b, ll i) {
    if (b >= 1) {
        ll m = 0;
        // keep the leg (r = b): remove i boxes from the arm -> mu = (a-i, 1^b)
        if (a - i >= 1) m += fhook(a - i, b);
        // remove one leg box (r = b-1): mu = (a-i+1, 1^(b-1))
        if (b - 1 >= 0) {
            ll c = a - i + 1;
            if (c >= 1 && c <= a) m += fhook(c, b - 1);
        }
        return m;
    }
    // b == 0: lambda = (a) single row, trivial rep -> multiplicity 1 for i<=a
    return (i <= a) ? 1 : 0;
}

// format a positive value (Num/Denom) in scientific notation, 10 sig. digits
string format_sci(const BigInt& Num, const BigInt& Denom) {
    long double val = Num.to_ld() / Denom.to_ld();
    int E = 0;
    if (val >= 1.0L) {
        while (val >= 10.0L) { val /= 10.0L; ++E; }
    } else {
        while (val < 1.0L) { val *= 10.0L; --E; }
    }
    char buf[64];
    snprintf(buf, sizeof(buf), "%.9Lf", val);
    string s = buf;
    // rounding may push the mantissa up to 10.000000000
    if (s == "10.000000000") { s = "1.000000000"; ++E; }
    string exp = (E >= 0 ? "+" : "-") + to_string(abs(E));
    return s + "e" + exp;
}

string solve(int k) {
    ll T = (ll)k * (k - 1) / 2 + 1;

    // lcm(1..T)
    ll lcmT = 1;
    for (ll i = 2; i <= T; ++i) lcmT = lcmT / gcd_ll(lcmT, i) * i;
    ll base = lcmT / T; // lcm of the binomial coefficients C(T-1, j)

    // binomial row C(T-1, j), j = 0..T-1
    vector<ll> d(T);
    for (ll j = 0; j < T; ++j) d[j] = binom(T - 1, j);

    BigInt pos, neg;

    for (ll a = 1; a <= T; ++a) {
        ll b = T - a;
        ll da = d[a - 1];           // C(T-1, a-1)
        ll chi = (b % 2 == 0) ? 1 : -1;
        ll ratio = base / da;       // exact integer (da | base)

        BigInt term(1);
        for (int t = 0; t < k - 1; ++t) term = BigInt::mulSmall(term, ratio);
        for (int i = 1; i <= k; ++i)
            term = BigInt::mulSmall(term, multiplicity(a, b, i));

        if (chi > 0) pos = BigInt::add(pos, term);
        else neg = BigInt::add(neg, term);
    }

    BigInt Num = BigInt::sub(pos, neg);
    BigInt Denom(1);
    for (int t = 0; t < k - 1; ++t) Denom = BigInt::mulSmall(Denom, base);
    for (ll i = 1; i <= T; ++i) Denom = BigInt::mulSmall(Denom, i); // T!

    return format_sci(Num, Denom);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int k;
    cin >> k;
    cout << solve(k) << "\n";
    return 0;
}
