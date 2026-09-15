// PE 326 - Modulo Summations (Brute Force for verification)
// Direct O(N) simulation with 64-bit, only works for small N

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N, M;
    cin >> N >> M;
    
    vector<ll> cnt(M, 0);
    cnt[0] = 1;
    
    ll T = 0;  // sum of k*a_k
    ll S_mod = 0;
    
    for (ll n = 1; n <= N; n++) {
        ll an;
        if (n == 1) {
            an = 1;
        } else {
            an = T % n;
        }
        T += n * an;
        S_mod = (S_mod + an) % M;
        cnt[S_mod]++;
    }
    
    ll ans = 0;
    for (ll r = 0; r < M; r++) {
        ll c = cnt[r];
        ans += c * (c - 1) / 2;
    }
    
    cout << ans << "\n";
    return 0;
}
