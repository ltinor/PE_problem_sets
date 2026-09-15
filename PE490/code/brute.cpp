#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: enumerate all jump sequences
ll brute_frog(int N, int max_jump) {
    const ll MOD = 1000000007LL;
    vector<ll> dp(N + 1, 0);
    dp[0] = 1;
    for (int pos = 0; pos < N; pos++) {
        for (int jump = 1; jump <= max_jump && pos + jump <= N; jump++) {
            dp[pos + jump] = (dp[pos + jump] + dp[pos]) % MOD;
        }
    }
    ll total = 0;
    for (int i = 1; i <= N; i++) total = (total + dp[i]) % MOD;
    return total;
}

int main() {
    ll N, K; cin >> N >> K;
    cout << brute_frog(N, K) << "\n";
}
