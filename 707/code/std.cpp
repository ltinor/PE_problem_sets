#include <bits/stdc++.h>
using namespace std;
#define ll long long

// PE707: Lights Out Variant
// F(w,h) = 2^{w*h - d(w,h)} where
// d(w,h) = deg(gcd(f_{w+1}(x+1), f_{h+1}(x)))
// f_0=0, f_1=1, f_{n+1}=x*f_n + f_{n-1} over GF(2)
// Answer: S(199,199) = sum_{k=1}^{199} F(199, fib_k) mod 1e9+7

const int MOD = 1000000007;
const int MODM1 = MOD - 1;
const int W = 199;
const int MAX_DEG = 512;

// Polynomial over GF(2), represented as bitset
struct Poly {
    bitset<MAX_DEG> c;
    Poly() { c.reset(); }
    Poly(ll x) { c.reset(); c.set(x); } // x^... no, monomial
    Poly(int deg, bool) { c.reset(); if (deg >= 0) c.set(deg); }
    
    int deg() const {
        for (int i = MAX_DEG-1; i >= 0; i--)
            if (c[i]) return i;
        return -1;
    }
    
    Poly operator+(const Poly& o) const { Poly r; r.c = c ^ o.c; return r; }
    Poly operator-(const Poly& o) const { return *this + o; }
    
    Poly operator*(const Poly& o) const {
        Poly r;
        for (int i = 0; i < MAX_DEG; i++) {
            if (c[i]) {
                r.c ^= (o.c << i);
            }
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
    
    static Poly gcd(Poly a, Poly b) {
        while (!b.is_zero()) {
            Poly t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
};

// f_n(x) over GF(2): f_0=0, f_1=1, f_{n+1}=x*f_n + f_{n-1}
Poly f_seq[205]; // f_0 ... f_201

void init_f() {
    f_seq[0] = Poly(); // 0
    f_seq[1].c.set(0); // 1
    for (int n = 1; n <= 201; n++) {
        // f_{n+1} = x * f_n + f_{n-1}
        Poly xfn = f_seq[n];
        xfn.c <<= 1; // multiply by x
        f_seq[n+1] = xfn + f_seq[n-1];
    }
}

// Substitute x -> x+1 in polynomial p
Poly sub_xp1(const Poly& p) {
    Poly r;
    for (int i = 0; i < MAX_DEG; i++) {
        if (p.c[i]) {
            // Add (x+1)^i to result
            // (x+1)^i = sum_{j=0}^{i} C(i,j) x^j
            // Over GF(2), C(i,j) mod 2 = 1 iff (j & ~i) == 0
            for (int j = 0; j <= i; j++) {
                if ((j & ~i) == 0) { // j is subset of i in binary
                    r.c.flip(j);
                }
            }
        }
    }
    return r;
}

// Compute f_n(x) mod g using fast doubling
// Using matrix [[x, 1], [1, 0]]^n
Poly fib_poly_mod(ll n, const Poly& g) {
    if (n == 0) return Poly(); // f_0 = 0
    if (n == 1) { Poly r; r.c.set(0); return r; } // f_1 = 1
    
    // Matrix M = [[x, 1], [1, 0]]
    // M^n gives us f_{n+1}, f_n, f_n, f_{n-1}
    // We compute M^{n-1} to get f_n
    
    // Represent matrix as: [[a,b],[c,d]]
    struct Mat { Poly a, b, c, d; };
    
    Mat base;
    base.a.c.set(1); // x
    base.b.c.set(0); // 1
    base.c.c.set(0); // 1
    base.d = Poly();  // 0
    
    Mat result;
    result.a.c.set(0); // 1
    result.b = Poly();  // 0
    result.c = Poly();  // 0
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
    
    // result = M^{n-1}
    // f_n = result.c (the (2,1) entry)
    // Check: for n=2, M^1 = [[x,1],[1,0]], (2,1)=1, f_2=x. Hmm
    // Actually [f_n, f_{n-1}]^T = M^{n-1} [f_1, f_0]^T = M^{n-1} [1, 0]^T
    // = [result.a, result.c]^T
    // So f_n = result.a ... let me check
    // For n=2: M^1 [1,0]^T = [x, 1]^T. So f_2 = x (the a component). Yes.
    // So f_n = result.a
    return result.a % g;
}

// Compute Fibonacci number f_k mod MODM1
ll fib_mod(ll k, ll mod) {
    if (k == 0) return 0;
    if (k == 1) return 1;
    ll a = 0, b = 1;
    for (ll i = 2; i <= k; i++) {
        ll c = (a + b) % mod;
        a = b; b = c;
    }
    return b;
}

ll modpow(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    init_f();
    
    // g(x) = f_{W+1}(x+1) = f_{200}(x+1)
    Poly g = sub_xp1(f_seq[W+1]);
    
    ll ans = 0;
    
    // Fibonacci numbers: f_1=1, f_2=1, f_3=2, ...
    ll fa = 1, fb = 1; // f_1, f_2
    
    for (int k = 1; k <= W; k++) {
        ll h = fa; // Fibonacci number F_k
        
        // Compute p(x) = f_{h+1}(x) mod g(x)
        Poly p = fib_poly_mod(h + 1, g);
        
        // d = deg(gcd(g, p))
        Poly gd = Poly::gcd(g, p);
        int d = gd.deg();
        
        // F(199, h) = 2^{199*h - d} mod MOD
        ll exponent = ((ll)W * (h % MODM1) - d) % MODM1;
        if (exponent < 0) exponent += MODM1;
        ll F_val = modpow(2, exponent, MOD);
        
        ans = (ans + F_val) % MOD;
        
        // Next Fibonacci number
        if (k < W) {
            ll fc = (fa + fb) % MODM1;
            fa = fb;
            fb = fc;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
