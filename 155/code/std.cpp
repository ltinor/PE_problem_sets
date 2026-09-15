#include<bits/stdc++.h>
using namespace std;

#define ll long long

// PE 155: Capacitor Circuits - D(N): number of distinct total capacitance
// Using DP: for n capacitors, consider splitting into k and n-k groups
// Series: C = 1/(1/C1 + 1/C2)  → num/den = (n1*d2 + n2*d1) / (d1*d2)...no
// Parallel: C = C1 + C2 → num/den = (n1*d2 + n2*d1)/(d1*d2)
//
// Better: use fraction (num, den) in lowest terms
// Parallel: (n1/d1) + (n2/d2) = (n1*d2 + n2*d1)/(d1*d2)
// Series: 1 / (d1/n1 + d2/n2) = 1 / ((d1*n2 + d2*n1)/(n1*n2)) = (n1*n2)/(d1*n2 + d2*n1)
//   = (n1*n2) / (d1*n2 + d2*n1)

ll mygcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

struct Frac {
    ll num, den;
    Frac(ll n = 0, ll d = 1) : num(n), den(d) {
        if (den < 0) { num = -num; den = -den; }
        ll g = mygcd(abs(num), den);
        num /= g; den /= g;
    }
    bool operator<(const Frac& o) const {
        // Compare a/b < c/d using cross product
        __int128_t left = (__int128_t)num * o.den;
        __int128_t right = (__int128_t)o.num * den;
        return left < right;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // sets[n] = set of distinct capacitance values using exactly n capacitors
    vector<set<Frac>> exact(N + 1);
    exact[1].insert(Frac(1, 1));
    
    for (int n = 2; n <= N; n++) {
        for (int k = 1; k <= n/2; k++) {
            int nk = n - k;
            for (const Frac& a : exact[k]) {
                for (const Frac& b : exact[nk]) {
                    // Parallel: a + b
                    {
                        ll num = a.num * b.den + b.num * a.den;
                        ll den = a.den * b.den;
                        ll g = mygcd(abs(num), den);
                        exact[n].insert(Frac(num/g, den/g));
                    }
                    // Series: 1/(1/a + 1/b) = (a.num*b.num) / (a.den*b.num + b.den*a.num)
                    {
                        ll num = a.num * b.num;
                        ll den = a.den * b.num + b.den * a.num;
                        if (den == 0) continue;
                        ll g = mygcd(abs(num), den);
                        exact[n].insert(Frac(num/g, den/g));
                    }
                }
            }
        }
    }
    
    // D(N) = distinct values using UP TO N capacitors
    set<Frac> all;
    for (int n = 1; n <= N; n++) {
        for (const Frac& f : exact[n]) {
            all.insert(f);
        }
    }
    
    cout << all.size() << "\n";
    return 0;
}
