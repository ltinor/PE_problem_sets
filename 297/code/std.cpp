#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Precompute Fibonacci and dp
vector<ll> fib;
vector<ll> dp; // dp[i] = S(fib[i]) = sum_{n=1}^{fib[i]-1} z(n)

// Compute S(N) = sum_{n=1}^{N-1} z(n)
ll S(ll N) {
    if (N <= 1) return 0;
    // Find largest fib[k] < N
    int k = upper_bound(fib.begin(), fib.end(), N-1) - fib.begin() - 1;
    // fib[k] <= N-1, meaning fib[k] < N
    if (k <= 0) return 0;
    return dp[k] + (N - fib[k]) + S(N - fib[k]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Generate Fibonacci: F[1]=1, F[2]=2, F[3]=3, ...
    fib.push_back(0); // fib[0]=0 (sentinel)
    fib.push_back(1);
    fib.push_back(2);
    while (fib.back() <= N) {
        fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
    }

    // dp[i] = S(fib[i])
    int K = fib.size() - 1;
    dp.resize(K + 1);
    dp[0] = dp[1] = 0; // S(1) = 0
    dp[2] = 1; // S(2) = z(1) = 1

    for (int i = 2; i < K; i++) {
        // S(fib[i+1]) = S(fib[i]) + fib[i-1] + S(fib[i-1])
        dp[i+1] = dp[i] + fib[i-1] + dp[i-1];
    }

    cout << S(N) << "\n";
    return 0;
}
