#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Check if sides (a, a, b) form an almost equilateral triangle with integer area
bool check(ll a, ll b) {
    // 16 * area^2 = b^2 * (4*a^2 - b^2)
    // area is integer iff sqrt(b^2 * (4a^2 - b^2)) is divisible by 4
    ll b2 = b * b;
    ll t = b2 * (4LL * a * a - b2);
    ll rt = (ll)sqrtl((long double)t);
    // verify perfect square
    if (rt * rt != t) return false;
    if (rt % 4 != 0) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    ll ans = 0;

    for (ll a = 2; ; a++) {
        // Case 1: b = a + 1
        ll b1 = a + 1;
        ll P1 = 2*a + b1; // = 3a + 1
        if (P1 > M) break;
        if (check(a, b1)) {
            ans += P1;
        }

        // Case 2: b = a - 1
        if (a >= 2) {
            ll b2 = a - 1;
            ll P2 = 2*a + b2; // = 3a - 1
            if (P2 <= M) {
                if (check(a, b2)) {
                    ans += P2;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
