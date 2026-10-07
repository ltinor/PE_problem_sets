#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        if ((i ^ (2*i) ^ (3*i)) == 0) {
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
