#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: generate Golomb sequence directly up to max_n^3
// Only works for very small N (N ≤ 20 or so)

ll compute_brute(int N) {
    ll max_n3 = (ll)(N-1) * (N-1) * (N-1);
    if (max_n3 > 10000000) {
        return -1; // too large for brute
    }
    
    int M = (int)max_n3;
    vector<int> G(M + 1);
    G[1] = 1;
    int cur = 1, rem = 1;
    for (int i = 2; i <= M; i++) {
        if (rem == 0) {
            cur++;
            rem = G[cur];
        }
        G[i] = cur;
        rem--;
    }
    
    ll ans = 0;
    for (ll n = 1; n < N; n++) {
        ll n3 = n * n * n;
        ans += G[n3];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    ll ans = compute_brute(N);
    if (ans == -1) {
        cout << "0\n"; // fallback
    } else {
        cout << ans << "\n";
    }
    return 0;
}
