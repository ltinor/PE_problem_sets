#include<bits/stdc++.h>
using namespace std;

#define ll long long

// PE 153 brute: enumerate all n ≤ N and find all Gaussian divisors
// O(N sqrt(N)) - only for small N

ll mygcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    ll ans = 0;
    
    for (ll n = 1; n <= N; n++) {
        // Find all a+bi with a>0, b≥0, (a²+b²)/gcd(a,b) | n
        for (ll a = 1; a * a <= n; a++) {
            for (ll b = 0; a * a + b * b <= n; b++) {
                ll norm = a * a + b * b;
                ll g = mygcd(a, b);
                ll m = norm / g;
                if (n % m == 0) {
                    ans += a;
                }
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
