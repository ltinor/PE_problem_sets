#include<bits/stdc++.h>
using namespace std;
#define ll long long

// For a given m, x_i = 2i/(m+1) maximizes the product P_m = ∏_{i=1}^m x_i^i
// P_m = ∏_{i=1}^m (2i/(m+1))^i = (2/(m+1))^{m(m+1)/2} * ∏_{i=1}^m i^i
// We compute P_m using double and floor it.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    ll ans = 0;

    for (int m = 2; m <= M; m++) {
        long double log_sum = 0.0L;
        for (int i = 1; i <= m; i++) {
            log_sum += i * logl(2.0L * i / (m + 1.0L));
        }
        long double P_m = expl(log_sum);
        ans += (ll)floorl(P_m);
    }

    cout << ans << "\n";
    return 0;
}
