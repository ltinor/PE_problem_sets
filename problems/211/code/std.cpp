#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 211: Sum of n ≤ N where σ₂(n) is a perfect square
// Original: N = 64,000,000, answer = 1922364685
// Adapted: N ≤ 10^7, parameterized

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // Sieve σ₂: for each i, add i² to all multiples
    vector<ll> sigma2(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        ll i2 = (ll)i * i;
        for (int j = i; j <= N; j += i) {
            sigma2[j] += i2;
        }
    }

    // Check for perfect squares
    ll ans = 0;
    for (int n = 1; n <= N; n++) {
        ll s = sigma2[n];
        ll r = (ll)sqrt((long double)s);
        // Check r² and (r+1)² to handle floating point issues
        if (r * r == s || (r + 1) * (r + 1) == s) {
            ans += n;
        }
    }

    cout << ans << "\n";
}
