#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute: enumerate all subsets of Un, check polygon condition
// A set generates a polygon iff max < sum of rest (polygon inequality)

int main() {
    ll n; cin >> n;
    vector<ll> s(n+1);
    s[1]=1; s[2]=2; s[3]=3;
    for (int i=4; i<=n; i++) s[i]=s[i-1]+s[i-3];

    ll ans = 0;
    int total = 1<<n;
    for (int mask=1; mask<total; mask++) {
        if (__builtin_popcount(mask) < 3) continue;
        ll sum=0, mx=0;
        for (int i=0; i<n; i++) {
            if (mask>>i & 1) {
                sum += s[i+1];
                mx = max(mx, s[i+1]);
            }
        }
        if (mx < sum - mx) ans++;
    }
    cout << ans << "\n";
}
