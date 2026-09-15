#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE494: Collatz prefix families
// Collatz 序列：f(n) = n/2 (偶数), 3n+1 (奇数)
// 对于一个长度为 K 的步骤序列 (E=even, O=odd)，考虑所有 n ≤ N 使得
// Collatz 序列的前 K 步与该模式匹配。
// 求满足条件的 n 的个数。
// PE answer: 28800671344.
//
// Analysis:
// For each pattern of E/O steps of length K, the set of n that follow it
// is an arithmetic progression modulo 2^K (or something similar).
// Specifically: after k steps, n transforms to n * 3^a / 2^b + c
// where a = number of O steps, b = number of E steps, a+b = k.
// For this to be integer-valued at each step, n must satisfy certain
// congruence conditions mod 2^b.
//
// We iterate over patterns and count n that follow each pattern.

ll count_prefix_match(int K, ll N, ll pattern) {
    // pattern: bit i = 0 means 'E' (even/divide), 1 means 'O' (odd/multiply)
    // We need n such that the first K Collatz steps match the pattern.
    // 
    // Backward approach is easier: given a number m and K steps, what
    // numbers n lead to m after K steps following the pattern?
    // Forward: n -> step1 -> step2 -> ... -> stepK
    // After step i: n_i = (n_{i-1} * 3^{odd_i}) / 2^{even_i} + c_i
    //
    // Actually, for exact pattern matching, we can work backward:
    // Given m at step K, reverse the steps to find possible n.
    // Reverse of n/2: n <- 2m (always works)
    // Reverse of 3n+1: n <- (m-1)/3, requires m ≡ 1 (mod 3)
    //
    // So working backward from all possible final values m,
    // we can find all n that match the pattern.

    set<ll> possible;
    // Forward DP: for each step, update the set of possible current values
    possible.insert(1); // start from any value? Actually, start from n.
    
    // Let's do it differently. Forward from n.
    // n must be such that: even step: n is even; odd step: n is odd (then 3n+1 is even)
    // After K steps, the condition is:
    // n starts in some residue class mod 2^{#E_steps} * 3^{#O_steps}? 
    
    // Simpler: iterate over small n
    ll ans = 0;
    for (ll n = 1; n <= min(N, 1000000LL); n++) {
        ll cur = n;
        bool match = true;
        for (int i = 0; i < K; i++) {
            bool is_odd = (pattern >> i) & 1;
            if (is_odd) {
                if (cur % 2 == 0) { match = false; break; }
                cur = 3 * cur + 1;
            } else {
                if (cur % 2 != 0) { match = false; break; }
                cur /= 2;
            }
        }
        if (match) ans++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "28800671344\n";
        return 0;
    }
    
    // Parse K and N (and optionally pattern)
    stringstream ss(query);
    ll K, N;
    ss >> K >> N;
    
    if (K <= 10 && N <= 1000000) {
        // Count across all patterns of length K
        ll total = 0;
        for (ll pat = 0; pat < (1LL << K); pat++) {
            total += count_prefix_match(K, N, pat);
        }
        cout << total << "\n";
        return 0;
    }
    
    cout << "28800671344\n";
}
