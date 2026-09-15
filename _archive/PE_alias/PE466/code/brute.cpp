#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE466 brute: direct enumeration of all products
ll P_brute(ll m, ll n) {
    set<ll> s;
    for (ll i = 1; i <= m; i++)
        for (ll j = 1; j <= n; j++)
            s.insert(i * j);
    return s.size();
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll m, n; cin >> m >> n;
    cout << P_brute(m, n) << "\n";
}
