#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 211: Brute force - compute σ₂ by factoring each n
// Only usable for small N (≤ 10^5)

ll sigma2_brute(int n) {
    ll sum = 0;
    for (int d = 1; (ll)d * d <= n; d++) {
        if (n % d == 0) {
            sum += (ll)d * d;
            int d2 = n / d;
            if (d2 != d) sum += (ll)d2 * d2;
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll ans = 0;
    for (int n = 1; n <= N; n++) {
        ll s = sigma2_brute(n);
        ll r = (ll)sqrt((long double)s);
        if (r * r == s) ans += n;
    }

    cout << ans << "\n";
}
