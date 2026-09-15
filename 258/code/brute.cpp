#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll M = 20092010;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    // Brute force using DP with period detection
    // Since the recurrence g_k = g_{k-2000} + g_{k-1999} mod M,
    // and there are only D state variables, the state repeats
    // within at most M^D (impractical). But for small K, direct DP works.

    if (K < 100000) {
        vector<ll> g(K+1, 1);
        for (ll i = 2000; i <= K; i++) {
            g[i] = (g[i-2000] + g[i-1999]) % M;
        }
        cout << g[K] << "\n";
    } else {
        // For large K, we use period detection on the 2000-element state vector
        // Combined state: (g_{k-1999}, ..., g_k) has M^2000 possibilities,
        // so for practical purposes we trust std.cpp
        cout << 0 << "\n"; // Placeholder
    }

    return 0;
}
