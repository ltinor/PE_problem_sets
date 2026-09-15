#include <bits/stdc++.h>
using namespace std;
#define ll long long

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
        for (int i = 0; i < MAX_DEG; i++) {
            if (c[i]) r.c ^= (o.c << i);
        }
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

// Matrix exponentiation for f_n mod g
Poly fib_poly_mod(ll n, const Poly& g) {
    if (n == 0) return Poly();
    if (n == 1) { Poly r; r.c.set(0); return r; }
    
    struct Mat { Poly a, b, c, d; };
    Mat base;
    base.a.c.set(1); // x
    base.b.c.set(0); // 1
    base.c.c.set(0); // 1
    base.d = Poly();   // 0
    
    Mat result;
    result.a.c.set(0); // 1
    result.b = Poly();
    result.c = Poly();
    result.d.c.set(0); // 1
    
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

int main() {
    init_f(30);
    
    // Test: compute f_n for small n without mod and compare
    cout << "f_0: " << f_seq[0].deg() << " deg" << endl;
    cout << "f_1: " << f_seq[1].deg() << " deg" << endl;
    cout << "f_2 deg=" << f_seq[2].deg() << " x^1? " << f_seq[2].c[1] << endl;
    cout << "f_3 deg=" << f_seq[3].deg() << " x^2+1? " << f_seq[3].c[2] << f_seq[3].c[0] << endl;
    cout << "f_4 deg=" << f_seq[4].deg() << " x^3? " << f_seq[4].c[3] << endl;
    cout << "f_5 deg=" << f_seq[5].deg() << " x^4+x^2+1? " << f_seq[5].c[4] << f_seq[5].c[2] << f_seq[5].c[0] << endl;
    
    // Compare fib_poly_mod with direct for small n
    // Use g = 0 (no mod) for small n... but we need a mod for matrix ops.
    // Let's use a large-degree g that doesn't do anything for small n.
    Poly g_big;
    g_big.c.set(200); // x^200, won't affect small polys
    
    for (int n = 1; n <= 10; n++) {
        Poly direct = f_seq[n];
        Poly computed = fib_poly_mod(n, g_big);
        bool match = (direct.c == computed.c);
        cout << "n=" << n << " direct deg=" << direct.deg() << " comp deg=" << computed.deg() << " match=" << match << endl;
    }
    
    return 0;
}
