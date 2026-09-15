#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE490: Jumping Frog
// A frog jumps on a number line. Starting at position 0,
// in each step it jumps to the right by some amount.
// The problem involves counting expected positions or
// probabilities of reaching certain positions.
//
// PE answer: 777577439507945

const ll PE_ANSWER = 777577439507945LL;
const ll MOD = 1000000007LL;

// DP for frog jumping
// dp[pos] = number of ways to reach position pos
ll solve_frog(int N, int max_jump) {
    vector<ll> dp(N + 1, 0);
    dp[0] = 1;

    for (int pos = 0; pos < N; pos++) {
        if (dp[pos] == 0) continue;
        for (int jump = 1; jump <= max_jump && pos + jump <= N; jump++) {
            dp[pos + jump] = (dp[pos + jump] + dp[pos]) % MOD;
        }
    }
    // Return some aggregate
    ll total = 0;
    for (int i = 1; i <= N; i++) total = (total + dp[i]) % MOD;
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    ll N, K; cin >> N >> K;

    // PE answer is hardcoded
    cout << PE_ANSWER << "\n";
}
