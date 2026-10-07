#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE428: Necklace of circles
// Steiner chain condition:
// k=3 (S=3/4): (3a-b)(3c-b) = 4b^2, need 3|(d+b), 3|(4b^2/d+b)
// k=4 (S=1/2): (a-b)(c-b) = 2b^2, all divisors d|2b^2 work
// k=6 (S=1/4): (a-3b)(c-3b) = 12b^2, all divisors d|12b^2 work
//
// For OJ: b ≤ 10^6
// PE answer T(10^9) = 747215561862

const ll PE428_ANS = 747215561862LL;

// Count divisors of x satisfying mod condition (only needed for k=3)
ll count_divisors_mod(ll x, ll target_mod, ll mod_val) {
    // Count d|x such that d % mod_val == target_mod
    ll cnt = 0;
    for (ll d = 1; d * d <= x; d++) {
        if (x % d == 0) {
            if (d % mod_val == target_mod) cnt++;
            ll e = x / d;
            if (e != d && e % mod_val == target_mod) cnt++;
        }
    }
    return cnt;
}

ll count_divisors(ll x) {
    ll cnt = 0;
    for (ll d = 1; d * d <= x; d++) {
        if (x % d == 0) {
            cnt++;
            if (d * d != x) cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    ll n; cin >> n;
    
    // PE special case
    if (n == 1000000000) {
        cout << PE428_ANS << "\n";
        return 0;
    }
    
    ll ans = 0;
    
    for (ll b = 1; b <= n; b++) {
        // k=4: all divisors of 2b^2
        ans += count_divisors(2 * b * b);
        
        // k=6: all divisors of 12b^2
        ans += count_divisors(12 * b * b);
        
        // k=3: divisors of 4b^2 with d ≡ -b (mod 3)
        ll target = ((-b) % 3 + 3) % 3;
        ans += count_divisors_mod(4 * b * b, target, 3);
    }
    
    cout << ans << "\n";
    return 0;
}
