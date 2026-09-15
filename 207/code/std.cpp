#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 207: Integer Partition Equations
// Find smallest m with P(m) < a/b
// P(m) = (# perfect partitions with k <= m) / (# total partitions with k <= m)
// Perfect: k = 2^t(2^t - 1) for integer t >= 1
// Total: k = n(n-1) for integer n >= 2
// PE Answer (a=1, b=12345): m = 44043947822 ? Let's compute
// Actually we compute: input a b, output smallest m

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b;
    cin >> a >> b;
    // We need P(m) < a/b, i.e., perfect_count / total_count < a/b
    // perfect_count * b < total_count * a

    ll n = 2;  // pronic index: k = n(n-1)
    ll perf_count = 0;
    ll next_perfect_t = 1;
    ll next_perfect_k = (1LL << next_perfect_t) * ((1LL << next_perfect_t) - 1); // 2^1*(2^1-1) = 2

    ll ans = 0;

    while (true) {
        ll k = n * (n - 1); // current pronic number (total partition boundary)

        // Update perfect count up to k
        while (next_perfect_k <= k) {
            perf_count++;
            next_perfect_t++;
            next_perfect_k = (1LL << next_perfect_t) * ((1LL << next_perfect_t) - 1);
            if (next_perfect_k < 0) break; // overflow protection
        }

        // total_count = n - 1 (number of n >= 2 with n(n-1) <= k)
        ll total_count = n - 1;

        // Check P(m) at m = k
        // P(k) = perf_count / total_count < a/b
        // perf_count * b < total_count * a
        if (perf_count * b < total_count * a) {
            ans = k;
            break;
        }

        n++;
        if (n > 200000000) break; // safety
    }

    cout << ans << "\n";
    return 0;
}
