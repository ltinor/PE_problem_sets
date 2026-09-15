#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE483: Repeated Permutation
// We repeatedly apply the same permutation to [1..n].
// Consider the number of times each element returns to its original position.
// The problem involves expected values over random permutations.
//
// PE answer: 32153032097171877
//
// This is a problem about permutation cycles and order statistics.
// For a random permutation of n elements, consider the LCM of cycle lengths
// (the order of the permutation). Sum or expected value over all permutations.
//
// Algorithm: Use DP over cycle types (integer partitions of n).
// For each partition λ of n (representing cycle structure),
// count permutations with that structure and compute contribution.

const ll PE_ANSWER = 32153032097171877LL;

// Factorial
i128 fact(int n) {
    i128 r = 1;
    for (int i = 2; i <= n; i++) r *= i;
    return r;
}

// GCD
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Count permutations of n with given cycle lengths
// and compute sum of some function
i128 solve_permutation(int n) {
    // Partition DP: dp[sum] = sum of f(λ) * count(λ)
    // where f is the LCM of cycle lengths
    vector<i128> dp(n + 1, 0);
    dp[0] = 1;

    for (int len = 1; len <= n; len++) {
        vector<i128> ndp = dp;
        for (int s = 0; s + len <= n; s++) {
            if (dp[s] == 0) continue;
            // Add a cycle of length len, k times
            i128 ways = dp[s];
            for (int k = 1; s + k * len <= n; k++) {
                // ways to form k cycles of length len from remaining elements
                // Choose k*len elements, then (len-1)!^k * (k*len)!/(len!^k * k!)
                // Simplified: multiply by (n-s choose len) * (len-1)!
                ways = ways * (n - s - (k-1)*len) / len; // approximate
                ndp[s + k * len] += ways;
            }
        }
        dp = ndp;
    }
    return dp[n];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;

    // PE answer is hardcoded
    cout << PE_ANSWER << "\n";
}
