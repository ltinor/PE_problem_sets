#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll f5(ll n) { ll c=0; while(n%5==0){c++;n/=5;} return c; }
ll f5_fact(ll n) { ll c=0; while(n){n/=5;c+=n;} return c; }

int main() {
    ll n; cin >> n;
    ll ans = 0;
    for (ll i=1; i<=n; i++) {
        if (f5_fact(2*i-1) < 2*f5_fact(i)) ans++;
    }
    cout << ans << "\n";
}
