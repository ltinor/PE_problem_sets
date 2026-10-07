#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    long long ans = 0;

    for (int m = 2; m <= M; m++) {
        long double log_sum = 0.0L;
        for (int i = 1; i <= m; i++) {
            log_sum += i * logl(2.0L * i / (m + 1.0L));
        }
        long double P_m = expl(log_sum);
        ans += (long long)floorl(P_m);
    }

    cout << ans << "\n";
    return 0;
}
