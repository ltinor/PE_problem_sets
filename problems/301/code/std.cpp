#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Count numbers <= n with no consecutive 1 bits in binary
// This is equivalent to n ^ (2*n) ^ (3*n) == 0
ll count_no_consecutive_ones(ll n) {
    if (n <= 0) return 0;
    // DP: fib[i] = count of i-bit numbers with no consecutive 1s
    // fib[1]=2 (0,1), fib[2]=3 (00,01,10), fib[i]=fib[i-1]+fib[i-2]
    vector<ll> fib(64);
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < 64; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    ll ans = 0;
    int prev_bit = 0;
    for (int i = 62; i >= 0; i--) {
        if (n & (1LL << i)) {
            // Count all numbers with this bit = 0 (and i remaining bits)
            ans += fib[i];
            if (prev_bit) {
                // Two consecutive 1s would appear, stop
                return ans;
            }
            prev_bit = 1;
        } else {
            prev_bit = 0;
        }
    }
    // Include n itself
    ans += 1;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    // We need count for n <= N where n^(2n)^(3n)=0, excluding 0
    ll ans = count_no_consecutive_ones(n) - 1; // exclude 0
    cout << ans << "\n";

    return 0;
}
