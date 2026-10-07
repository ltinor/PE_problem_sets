#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int M, K; cin >> M >> K;
    
    vector<int> cnt(M + 1, 0);
    // For each outer side a, thickness k: t = 4*k*(a-k)
    // Need a-k >= k+1 (hole positive) => a >= 2k+1
    for (int a = 3; a <= M; a++) {
        for (int k = 1; k * 2 < a; k++) {
            ll t = 4LL * k * (a - k);
            if (t > M) break;
            cnt[t]++;
        }
    }
    
    // N[n] = count of t where cnt[t] == n
    vector<int> N(K + 1, 0);
    for (int t = 1; t <= M; t++) {
        if (cnt[t] >= 1 && cnt[t] <= K)
            N[cnt[t]]++;
    }
    
    ll ans = 0;
    for (int n = 1; n <= K; n++) ans += N[n];
    cout << ans << "\n";
}
