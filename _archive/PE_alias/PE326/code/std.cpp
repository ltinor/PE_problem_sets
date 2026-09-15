#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE326: Modulo Summations
// a_1 = 1 (base case)
// a_n = (sum_{k=1}^{n-1} k*a_k) mod n  for n > 1
// f(N,M) = number of pairs (p,q), 1≤p≤q≤N, with sum_{i=p}^{q} a_i ≡ 0 (mod M)

// For OJ: N ≤ 10^6, M ≤ 1000. Direct O(N) computation.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N, M;
    cin >> N >> M;
    
    vector<ll> cnt(M, 0);
    cnt[0] = 1; // P_0 = 0
    
    ll S = 0;        // sum_{k=1}^{n-1} k*a_k (for computing next a_n)
    ll P_mod = 0;    // prefix sum mod M
    
    // n = 1: a_1 = 1 (base case)
    if (N >= 1) {
        ll a1 = 1;
        P_mod = (P_mod + a1) % M;
        cnt[P_mod]++;
        S = 1 * a1; // S_2 = sum_{k=1}^{1} k*a_k = 1*1 = 1
    }
    
    for (ll n = 2; n <= N; n++) {
        // a_n = S mod n
        ll a = S % n;
        
        // Update prefix sum mod M
        P_mod = (P_mod + a) % M;
        cnt[P_mod]++;
        
        // Update S for next: S_{n+1} = S_n + n * a_n
        S += n * a;
    }
    
    // Count pairs: for each residue r, C(cnt[r], 2)
    ll ans = 0;
    for (ll r = 0; r < M; r++) {
        ans += cnt[r] * (cnt[r] - 1) / 2;
    }
    
    cout << ans << "\n";
    return 0;
}
