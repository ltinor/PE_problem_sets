#include<bits/stdc++.h>
using namespace std;
#define ll long long
// Brute: compute S sequence, then game theory (Grundy/impartial game)
// sk = count of 1s in binary of 0..k
int main() {
    ll N; cin >> N;
    // compute S up to some bound
    const int MAX = 100000;
    vector<ll> S(MAX+1);
    S[0] = 0;
    for (int i=1; i<=MAX; i++) {
        S[i] = S[i-1] + __builtin_popcount(i);
    }
    // For each n, compute M(n) via game theory
    ll ans = 0;
    for (ll n=1; n<=N; n++) {
        // Find winning positions in S
        // This is an impartial game: position c is losing if all c+k in S are winning
        // Simplified brute
        ll m = 0;
        // Check each first move 1..n
        for (ll f=n; f>=1; f--) {
            if (binary_search(S.begin(), S.end(), f)) {
                // Check if this move leads to a winning position
                // for brute just take the max f in S
                m = f; break;
            }
        }
        ans += m*m*m;
    }
    cout << ans << "\n";
}
