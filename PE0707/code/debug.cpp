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
    
    static Poly gcd(Poly a, Poly b) {
        while (!b.is_zero()) {
            Poly t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    
    void print() const {
        bool first = true;
        for (int i = deg(); i >= 0; i--) {
            if (c[i]) {
                if (!first) cout << " + ";
                cout << "x^" << i;
                first = false;
            }
        }
        if (first) cout << "0";
        cout << "\n";
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
                if ((j & ~i) == 0) {
                    r.c.flip(j);
                }
            }
        }
    }
    return r;
}

int main() {
    init_f();
    
    // Test 1D case: w=1, g(x) = f_2(x+1) = x+1
    cout << "f_2(x) = "; f_seq[2].print();
    Poly g1 = sub_xp1(f_seq[2]);
    cout << "g_1(x) = f_2(x+1) = "; g1.print();
    
    // Test f_3(x) = x^2+1
    cout << "f_3(x) = "; f_seq[3].print();
    
    // gcd(g1, f_2(x)) should be 1
    Poly gd = Poly::gcd(g1, f_seq[2]);
    cout << "gcd(g1, f_2) deg = " << gd.deg() << " (expected -1)" << endl;
    
    // gcd(g1, f_3(x)) = gcd(x+1, x^2+1) should be x+1
    gd = Poly::gcd(g1, f_seq[3]);
    cout << "gcd(g1, f_3) deg = " << gd.deg() << " (expected 1)" << endl;
    
    // Test w=3: g = f_4(x+1) = (x+1)^3
    Poly g3 = sub_xp1(f_seq[4]);
    cout << "g_3(x) = f_4(x+1) = "; g3.print();
    // Expect x^3+x^2+x+1
    // gcd(g3, f_4(x)) = gcd(x^3+x^2+x+1, x^3) = 1
    gd = Poly::gcd(g3, f_seq[4]);
    cout << "gcd(g3, f_4) deg = " << gd.deg() << " (expected -1 or 0)" << endl;
    
    // Test w=4: g = f_5(x+1) = (x+1)^4+(x+1)^2+1 = x^4+x^2+1
    Poly g4 = sub_xp1(f_seq[5]);
    cout << "g_4(x) = f_5(x+1) = "; g4.print();
    gd = Poly::gcd(g4, f_seq[5]);
    cout << "gcd(g4, f_5) deg = " << gd.deg() << " (expected 4)" << endl;
    
    return 0;
}
