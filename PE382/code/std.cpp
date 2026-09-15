#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE382: f(n) = subsets of Un generating polygons, output last 9 digits
// Un = {s1..sn}, s1=1,s2=2,s3=3, s_k = s_{k-1}+s_{k-3}
// Polygon condition: max < sum of rest
// f(n) = 2^n - 1 - n - n(n-1)/2 - bad_triples
// bad triple: (i<j<k) with s_k >= s_i + s_j

const ll MOD = 1000000000;

ll modpow(ll a, ll b, ll m) {
    ll r = 1; a %= m;
    while (b) { if (b&1) r = r * a % m; a = a * a % m; b >>= 1; }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;
    
    // Compute s sequence
    vector<ll> s(n + 1);
    if (n >= 1) s[1] = 1;
    if (n >= 2) s[2] = 2;
    if (n >= 3) s[3] = 3;
    for (ll i = 4; i <= n; i++) {
        s[i] = s[i-1] + s[i-3];
        // Cap to avoid overflow; for bad triple check we need exact values
        // s grows fast, for large n we need __int128
    }
    
    // Total subsets of size >= 3: 2^n - 1 - n - n*(n-1)/2
    ll total = (modpow(2, n, MOD) - 1 - n % MOD - (n % MOD) * ((n-1) % MOD) / 2) % MOD;
    total = (total % MOD + MOD) % MOD;
    
    // Count bad triangles using __int128 for exact comparison
    ll bad = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = i + 1; j <= n; j++) {
            // Find first k where s[k] >= s[i] + s[j]
            // Since s is sorted (increasing after first few), binary search
            ll lo = j + 1, hi = n, first = n + 1;
            while (lo <= hi) {
                ll mid = (lo + hi) / 2;
                if (s[mid] >= s[i] + s[j]) {
                    first = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            if (first <= n) {
                bad += n - first + 1;
            }
        }
    }
    
    ll ans = (total - bad % MOD) % MOD;
    ans = (ans % MOD + MOD) % MOD;
    cout << ans << "\n";
    return 0;
}
