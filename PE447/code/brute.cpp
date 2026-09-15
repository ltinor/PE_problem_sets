#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE447 brute: enumerate all retractions for each n directly
ll R_brute(ll n) {
    if (n <= 1) return 0;
    ll cnt = 0;
    for (ll a = 1; a < n; a++) {
        if ((a * a) % n != a % n) continue;
        for (ll b = 0; b < n; b++) {
            if ((a * b) % n != 0) continue;
            cnt++;
        }
    }
    return cnt;
}

ll F_brute(ll N) {
    ll ans = 0;
    for (ll n = 2; n <= N; n++) {
        ans += R_brute(n);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    cout << F_brute(N) << "\n";
}
