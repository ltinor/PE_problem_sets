#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE448 brute: direct computation of S(n) for small n
ll my_gcd(ll a, ll b) { return b ? my_gcd(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    ll ans = 0;
    for (ll k = 1; k <= N; k++) {
        ll sum = 0;
        for (ll i = 1; i <= k; i++) {
            sum += k / my_gcd(k, i) * i;
        }
        ans += sum / k;
    }
    cout << ans << "\n";
}
