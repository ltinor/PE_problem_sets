#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force for PE 322
int main() {
    ll D, K;
    cin >> D >> K;

    ll m = 1;
    for (ll i = 0; i < D; i++) m *= 10;
    ll n = 1;
    for (ll i = 0; i < K; i++) n *= 10;
    n -= 10;

    ll ans = 0;
    for (ll i = n; i < m; i++) {
        // Check C(i,n) divisible by 10
        // Direct computation using binomial mod
        // Since this is brute, just count carries
        int carry2 = 0, carry5 = 0;
        ll a = n, b = i - n;

        // Count carries in base 2
        ll ta = a, tb = b;
        while (ta || tb) {
            if ((ta & 1) + (tb & 1) > 1) carry2++;
            ta >>= 1; tb >>= 1;
        }
        // Count carries in base 5
        ta = a, tb = b;
        while (ta || tb) {
            if ((ta % 5) + (tb % 5) >= 5) carry5++;
            ta /= 5; tb /= 5;
        }
        if (carry2 >= 1 && carry5 >= 1) ans++;
    }
    cout << ans << "\n";
    return 0;
}
