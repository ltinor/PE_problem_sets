#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Same logic as std but simpler types, for small n
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin >> n;
    ll ans = 0;
    ll mx = 2 * n;
    for (ll a = 1; a <= mx; a++) {
        for (ll b = a; b <= mx; b++) {
            for (ll c = b; c < a + b && c <= mx; c++) {
                ll s = a+b+c;
                ll D = s * (s-2*a) * (s-2*b) * (s-2*c);
                ll r = (ll)sqrt((long double)D);
                while ((r+1)*(r+1) <= D) r++;
                while (r*r > D) r--;
                if (r*r != D) continue;
                ll num = a*b*c;
                if (num % r != 0) continue;
                ll R = num / r;
                if (R <= n) ans += R;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
