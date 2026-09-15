#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;
const ll MOD = 1000000007LL;

// From std.cpp
i128 count_both_zero(ll N, int b) {
    ll B = 1LL << b;
    ll M = 2 * B;
    if (B > N) return (i128)(N + 1) * (N + 2) / 2;
    ll Q = N / M;
    ll R = N % M;
    auto sum_count = [&](ll limit) -> i128 {
        if (limit < 0) return 0;
        if (limit >= M) limit = M - 1;
        if (limit < B) return (i128)(limit + 1) * (limit + 2) / 2;
        i128 first = (i128)B * (B + 1) / 2;
        ll lo = 2 * B - 1 - limit;
        ll hi = B - 1;
        ll cnt = hi - lo + 1;
        i128 second = (i128)(lo + hi) * cnt / 2;
        return first + second;
    };
    i128 sum_all = (i128)B * B;
    i128 sum_rem = sum_count(R);
    return (i128)Q * (Q + 1) / 2 * sum_all + (i128)(Q + 1) * sum_rem;
}

ll G_fast(ll N) {
    i128 total_pairs = (i128)(N + 1) * (N + 2) / 2;
    ll ans = 0;
    for (int b = 0; (1LL << b) <= N; b++) {
        ll B = 1LL << b;
        i128 bz = count_both_zero(N, b);
        i128 bo = total_pairs - bz;
        ans = (ans + (ll)(bo % MOD) * (B % MOD)) % MOD;
    }
    // For bits where B > N: both_zero = total_pairs, so contribution = 0
    return ans * 2 % MOD;
}

ll G_brute_mod(ll N) {
    ll total = 0;
    for (ll n = 0; n <= N; n++) {
        for (ll k = 0; k <= n; k++) {
            ll m = n - k;
            ll g = (k ^ m) + (k | m) + (k & m);
            total = (total + g) % MOD;
        }
    }
    return total;
}

int main() {
    cout << "Verification for larger N:\n";
    vector<ll> tests = {10, 50, 100, 200, 500, 1000, 2000};
    for (ll N : tests) {
        ll f = G_fast(N);
        ll b = G_brute_mod(N);
        cout << "N=" << setw(5) << N << ": fast=" << setw(10) << f 
             << " brute=" << setw(10) << b << " "
             << (f == b ? "✓" : "✗") << "\n";
    }
    
    cout << "\nG(10^18) mod MOD = " << G_fast(1000000000000000000LL) << "\n";
    return 0;
}
