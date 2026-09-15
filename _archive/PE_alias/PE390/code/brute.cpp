#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE390 brute: enumerate b,c and compute area by formula sqrt(b^2c^2+b^2+c^2)/2
int main() {
    ll n; cin >> n;
    ll ans = 0;
    for (ll b = 1; b <= 2*n; b++) {
        ll max_c = 2*n / b;
        if (max_c < b) break;
        for (ll c = b; c <= max_c; c++) {
            ll val = b*b*c*c + b*b + c*c;
            ll k = (ll)sqrt((long double)val);
            while (k*k < val) k++;
            while (k*k > val) k--;
            if (k*k == val && k % 2 == 0) {
                ans += k / 2;
            }
        }
    }
    cout << ans << "\n";
}
