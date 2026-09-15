#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 197: f(x) = floor(2^(30.403243784 - x^2)) * 10^(-9)
// u_0 = -1, u_{n+1} = f(u_n)
// Find u_N + u_{N+1}
// Answer for N=10^12: 1.710637717

double f(double x) {
    double exponent = 30.403243784 - x * x;
    long long fl = (long long)pow(2.0, exponent);
    return fl * 1e-9;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    double u = -1.0;

    // For small N, iterate exactly
    if (N <= 100) {
        for (ll i = 0; i < N; i++) {
            u = f(u);
        }
        double ans = u + f(u);
        cout << fixed << setprecision(9) << ans << "\n";
        return 0;
    }

    // For large N: the sequence converges to a 2-cycle very quickly
    // The sum u_n + u_{n+1} stabilizes to a constant
    double sum = 0.0, prev_sum = -1e9;

    for (int i = 0; i < 10000; i++) {
        double v = f(u);
        sum = u + v;
        if (i > 50 && fabs(sum - prev_sum) < 1e-15) {
            break;
        }
        prev_sum = sum;
        u = v;
    }

    cout << fixed << setprecision(9) << sum << "\n";
}
