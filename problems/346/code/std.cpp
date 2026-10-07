#include<bits/stdc++.h>
using namespace std;
#define ll long long
using i128 = __int128;

// PE346: Sum of strong repunits < LIMIT
// A number is a strong repunit if it's a repunit in at least 2 bases b>1.
// Repunit in base b of length n: R(b,n) = (b^n-1)/(b-1), n≥2.
// Since R(b,2)=b+1, every number X≥2 has a repunit in base X-1 with n=2.
// So a strong repunit is any number that can be written as R(b,n) with n≥3
// (since n=2 always gives another representation). 1 is special.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll LIM;
    cin >> LIM;

    unordered_set<ll> repunits;
    repunits.insert(1); // 1 is trivially a strong repunit

    // Enumerate base b≥2, length n≥3
    for (ll b = 2; ; b++) {
        i128 val = (i128)b*b + b + 1; // n=3: b^2+b+1
        if (val > LIM) break;

        i128 p = (i128)b * b * b; // b^3
        for (ll n = 3; ; n++) {
            // R(b,n) = (b^n-1)/(b-1) = 1 + b + b^2 + ... + b^{n-1}
            // Compute iteratively
            if (val <= LIM) {
                repunits.insert((ll)val);
            } else {
                break;
            }
            p *= b;
            i128 next = (p - 1) / (b - 1);
            if (next > LIM) break;
            val = next;
        }
    }

    ll ans = 0;
    for (ll x : repunits) ans += x;
    cout << ans << "\n";
    return 0;
}
