#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE451 brute: compute I(n) by checking all m < n-1 for m² ≡ 1 (mod n)
ll I_brute(ll n) {
    ll best = 1;
    for (ll m = 2; m < n - 1; m++) {
        if ((m * m - 1) % n == 0) best = m;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;
    cout << I_brute(n) << "\n";
}
