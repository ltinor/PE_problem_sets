#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 207: Brute force - same algorithm, simpler loop
// For verification with small a, b values

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b;
    cin >> a >> b;

    ll n = 2;
    ll perf_count = 0;
    ll next_perfect_t = 1;
    ll next_perfect_k = 2; // 2^1*(2^1-1) = 2

    ll ans = 0;

    while (n <= 2000000) {
        ll k = n * (n - 1);

        while (next_perfect_k <= k && next_perfect_k > 0) {
            perf_count++;
            next_perfect_t++;
            ll p = (1LL << next_perfect_t);
            if (p > 1000000000) { next_perfect_k = -1; break; }
            next_perfect_k = p * (p - 1);
        }

        ll total_count = n - 1;

        if (perf_count * b < total_count * a) {
            ans = k;
            break;
        }

        n++;
    }

    cout << ans << "\n";
    return 0;
}
