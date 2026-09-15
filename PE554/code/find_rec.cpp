#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Gaussian elimination over rationals
struct Rat {
    ll num, den;
    Rat(ll n=0, ll d=1) : num(n), den(d) { reduce(); }
    void reduce() {
        if (den < 0) num=-num, den=-den;
        ll g = gcd(abs(num), den);
        num /= g; den /= g;
    }
    Rat operator+(Rat o) const { return Rat(num*o.den+o.num*den, den*o.den); }
    Rat operator-(Rat o) const { return Rat(num*o.den-o.num*den, den*o.den); }
    Rat operator*(Rat o) const { return Rat(num*o.num, den*o.den); }
    Rat operator/(Rat o) const { return Rat(num*o.den, den*o.num); }
    bool is_int() const { return den == 1; }
    ll to_ll() const { return num/den; }
};

vector<ll> gauss(vector<vector<Rat>> a) {
    int n = a.size();
    for (int col=0, row=0; col<n && row<n; col++) {
        int sel = row;
        for (int i=row; i<n; i++) if (a[i][col].num != 0) { sel=i; break; }
        if (a[sel][col].num == 0) continue;
        swap(a[sel], a[row]);
        Rat div = a[row][col];
        for (int j=col; j<=n; j++) a[row][j] = a[row][j] / div;
        for (int i=0; i<n; i++) {
            if (i != row && a[i][col].num != 0) {
                Rat factor = a[i][col];
                for (int j=col; j<=n; j++) a[i][j] = a[i][j] - factor * a[row][j];
            }
        }
        row++;
    }
    vector<ll> res(n);
    for (int i=0; i<n; i++) res[i] = a[i][n].to_ll();
    return res;
}

int main() {
    vector<ll> C = {0, 4, 25, 120, 497, 1924, 7265, 27288, 102745, 388692, 1477721, 5643064, 21632785, 83204260, 320932177, 1240939448};
    
    for (int order = 2; order <= 5; order++) {
        int n = order;
        vector<vector<Rat>> mat(n, vector<Rat>(n+1));
        for (int i=0; i<n; i++) {
            int idx = n + i + 1; // C[n+i+1]
            for (int j=0; j<n; j++) {
                mat[i][j] = Rat(C[idx - 1 - j]);
            }
            mat[i][n] = Rat(C[idx]);
        }
        auto coeffs = gauss(mat);
        cout << "Order " << order << ": ";
        for (int i=0; i<n; i++) cout << coeffs[i] << " ";
        
        // Verify
        bool ok = true;
        for (int i=n+1; i<(int)C.size(); i++) {
            ll pred = 0;
            for (int j=0; j<n; j++) pred += coeffs[j] * C[i-1-j];
            if (pred != C[i]) { ok = false; break; }
        }
        cout << (ok ? "OK" : "FAIL") << endl;
    }
    return 0;
}
