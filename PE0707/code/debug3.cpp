#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1000000007;
const int MODM1 = MOD - 1;
const int W = 199;
const int MAX_DEG = 512;

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

Poly f_seq[205];
void init_f() {
    f_seq[0] = Poly();
    f_seq[1].c.set(0);
    for (int n = 1; n <= 201; n++) {
        Poly xfn = f_seq[n];
        xfn.c <<= 1;
        f_seq[n+1] = xfn + f_seq[n-1];
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

int main() {
    init_f();
    
    Poly g = sub_xp1(f_seq[W+1]);
    cout << "g deg = " << g.deg() << endl;
    cout << "g(0) = " << g.c[0] << endl;
    
    // Test F(199, 1)
    Poly p1 = fib_poly_mod(2, g); // f_2 = x
    cout << "f_2 deg = " << p1.deg() << " (should be 1)" << endl;
    Poly gd1 = Poly::gcd(g, p1);
    cout << "gcd(g, f_2) deg = " << gd1.deg() << endl;
    
    // Test F(199, 2) 
    Poly p2 = fib_poly_mod(3, g); // f_3 = x^2+1
    cout << "f_3 deg = " << p2.deg() << endl;
    Poly gd2 = Poly::gcd(g, p2);
    cout << "gcd(g, f_3) deg = " << gd2.deg() << endl;
    
    // Direct F(199, 1) computation
    ll h = 1;
    int d = 0;
    ll exponent = ((ll)W * (h % MODM1) - d) % MODM1;
    if (exponent < 0) exponent += MODM1;
    ll F1 = modpow(2, exponent, MOD);
    cout << "F(199,1) = " << F1 << endl;
    
    // Direct 2^199 mod MOD
    cout << "2^199 mod MOD = " << modpow(2, 199, MOD) << endl;
    
    return 0;
}
