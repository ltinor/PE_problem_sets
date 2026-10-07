#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: same algorithm, but simpler implementation
// for verification purposes

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

    // For small N, iterate exactly N steps and compute sum
    if (N <= 10000) {
        for (ll i = 0; i < N; i++) {
            u = f(u);
        }
        double ans = u + f(u);
        cout << fixed << setprecision(9) << ans << "\n";
        return 0;
    }

    // For large N, iterate to convergence
    double sum = 0.0, prev_sum = -1e9;
    for (int i = 0; i < 10000; i++) {
        double v = f(u);
        sum = u + v;
        if (i > 50 && fabs(sum - prev_sum) < 1e-15) break;
        prev_sum = sum;
        u = v;
    }

    cout << fixed << setprecision(9) << sum << "\n";
}
