#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE390: S(n) = sum of areas of triangles with sides sqrt(1+b^2), sqrt(1+c^2), sqrt(b^2+c^2)
// Area = sqrt(b^2*c^2 + b^2 + c^2) / 2
// For integer area: b^2*c^2 + b^2 + c^2 must be a perfect square with even root.
// Count each unordered pair (b,c) once.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;
    
    ll ans = 0;
    ll max_b = 2 * n;
    
    for (ll b = 1; b <= max_b; b++) {
        ll max_c = 2 * n / b;
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
    return 0;
}
