#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1000000007;
const int MODM1 = MOD - 1;
const int MAX_DEG = 256;

struct Poly {
    bitset<MAX_DEG> c;
    Poly() { c.reset(); }
    int deg() const {
        for (int i = MAX_DEG-1; i >= 0; i--)
            if (c[i]) return i;
        return -1;
    }
    Poly operator+(const Poly& o) const { Poly r; r.c = c ^ o.c; return r; }
    Poly operator*(const Poly& o) const {
        Poly r;
        for (int i = 0; i < MAX_DEG; i++)
            if (c[i]) r.c ^= (o.c << i);
        return r;
    }
    Poly operator%(const Poly& mod) const {
        Poly r = *this;
        int md = mod.deg();
        if (md < 0) return r;
        while (true) {
            int rd = r.deg();
            if (rd < md) break;
            int shift = rd - md;
            r.c ^= (mod.c << shift);
        }
        return r;
    }
    bool is_zero() const { return c.none(); }
    static Poly gcd(Poly a, Poly b) {
        while (!b.is_zero()) { Poly t = a % b; a = b; b = t; }
        return a;
    }
};

Poly f_seq[50];
void init_f(int n) {
    f_seq[0] = Poly();
    f_seq[1].c.set(0);
    for (int i = 1; i <= n; i++) {
        Poly xfn = f_seq[i];
        xfn.c <<= 1;
        f_seq[i+1] = xfn + f_seq[i-1];
    }
}

Poly sub_xp1(const Poly& p) {
    Poly r;
    for (int i = 0; i < MAX_DEG; i++) {
        if (p.c[i]) {
            for (int j = 0; j <= i; j++) {
                if ((j & ~i) == 0) r.c.flip(j);
            }
        }
    }
    return r;
}

Poly fib_poly_mod(ll n, const Poly& g) {
    if (n == 0) return Poly();
    if (n == 1) { Poly r; r.c.set(0); return r; }
    
    struct Mat { Poly a, b, c, d; };
    Mat base;
    base.a.c.set(1); base.b.c.set(0); base.c.c.set(0); base.d = Poly();
    
    Mat result;
    result.a.c.set(0); result.b = Poly(); result.c = Poly(); result.d.c.set(0);
    
    auto mul = [&](const Mat& m1, const Mat& m2) -> Mat {
        Mat r;
        r.a = ((m1.a * m2.a) + (m1.b * m2.c)) % g;
        r.b = ((m1.a * m2.b) + (m1.b * m2.d)) % g;
        r.c = ((m1.c * m2.a) + (m1.d * m2.c)) % g;
        r.d = ((m1.c * m2.b) + (m1.d * m2.d)) % g;
        return r;
    };
    
    ll e = n - 1;
    Mat cur = base;
    while (e) {
        if (e & 1) result = mul(result, cur);
        cur = mul(cur, cur);
        e >>= 1;
    }
    return result.a % g;
}

ll modpow(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) { if (e & 1) r = r * a % mod; a = a * a % mod; e >>= 1; }
    return r;
}

ll F_val(int w, ll h, const Poly& g) {
    Poly p = fib_poly_mod(h + 1, g);
    Poly gd = Poly::gcd(g, p);
    int d = gd.deg();
    ll exponent = ((ll)w * (h % MODM1) - d) % MODM1;
    if (exponent < 0) exponent += MODM1;
    return modpow(2, exponent, MOD);
}

ll compute_S(int w, int k_count) {
    init_f(w + 10);
    Poly g = sub_xp1(f_seq[w+1]);
    
    ll ans = 0;
    ll fa = 1, fb = 1;
    for (int k = 1; k <= k_count; k++) {
        ans = (ans + F_val(w, fa, g)) % MOD;
        ll fc = (fa + fb) % MODM1;
        fa = fb; fb = fc;
    }
    return ans;
}

int main() {
    cout << "S(3,3) = " << compute_S(3, 3) << " (expected 32)" << endl;
    cout << "S(4,5) = " << compute_S(4, 5) << " (expected 1052960)" << endl;
    cout << "S(5,7) = " << compute_S(5, 7) << " (expected 346547294)" << endl;
    return 0;
}
