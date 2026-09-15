#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE446 brute: enumerate all retractions for n^4+4 directly
// Only valid for very small n since n^4+4 grows fast

// Count retractions for a given modulus m
ll R_brute(ll m) {
    if (m <= 1) return 0;
    ll cnt = 0;
    for (ll a = 1; a < m; a++) {
        if ((a * a) % m != a % m) continue;
        for (ll b = 0; b < m; b++) {
            if ((a * b) % m != 0) continue;
            cnt++;
        }
    }
    return cnt;
}

ll F_brute(ll N) {
    ll ans = 0;
    for (ll n = 1; n <= N; n++) {
        ll m = n*n*n*n + 4;
        if (m > 1000000) break; // brute limit
        ans += R_brute(m);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    cout << F_brute(N) << "\n";
}
