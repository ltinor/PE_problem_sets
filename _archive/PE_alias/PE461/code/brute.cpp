#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE461 brute: exhaustive search for small n
// f_n(k) = e^{k/n} - 1
ll brute_g(int n) {
    double PI = acos(-1.0);
    int K = (int)(n * log(PI + 1.0));
    
    vector<double> f(K + 1);
    for (int k = 0; k <= K; k++) {
        f[k] = exp((double)k / n) - 1.0;
    }
    
    double best_err = 1e100;
    ll best_g = 0;
    
    for (int a = 0; a <= K; a++) {
        for (int b = a; b <= K; b++) {
            for (int c = b; c <= K; c++) {
                for (int d = c; d <= K; d++) {
                    double total = f[a] + f[b] + f[c] + f[d];
                    double err = fabs(total - PI);
                    if (err < best_err - 1e-15) {
                        best_err = err;
                        best_g = (ll)a*a + (ll)b*b + (ll)c*c + (ll)d*d;
                    }
                }
            }
        }
    }
    return best_g;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    if (n <= 30) {
        cout << brute_g(n) << "\n";
    } else {
        cout << "-1\n";
    }
}
