#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Reference / brute-force implementation of the same Gosper algorithm,
// written independently from std.cpp and using 128-bit integers for extra
// safety. Since α's continued fraction only contains 1's and 2's, β's partial
// quotients are bounded and the state never overflows, so __int128 is overkill
// but guarantees correctness on any input within the reduced range.
//
// This serves as the cross-check target for scripts/check.sh.

bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Lazy prime generator for α's term pattern.
    vector<ll> primes;
    ll next_cand = 2;
    auto ensure = [&](ll idx) {
        while ((ll)primes.size() <= idx) {
            while (!is_prime(next_cand)) ++next_cand;
            primes.push_back(next_cand);
            ++next_cand;
        }
    };

    // α terms: a_0 = 2, then for each prime p: p ones followed by one 2.
    ll alpha_emitted = 0, prime_idx = 0, run_pos = 0;
    auto next_alpha = [&]() -> ll {
        if (alpha_emitted == 0) { ++alpha_emitted; return 2; }
        ensure(prime_idx);
        if (run_pos < primes[prime_idx]) {
            ++run_pos; ++alpha_emitted; return 1;
        }
        run_pos = 0; ++prime_idx; ++alpha_emitted; return 2;
    };

    i128 a = 2, b = 3, c = 3, d = 2;   // Z = [[a,b],[c,d]] for β=(2α+3)/(3α+2)
    i128 sum = 0;
    ll out_count = 0;

    while (out_count < N) {
        if (c == 0 && d == 0) break;
        if (c == 0 || d == 0) {
            ll x = next_alpha();
            i128 na = a * x + b, nb = a, nc = c * x + d, nd = c;
            a = na; b = nb; c = nc; d = nd;
            continue;
        }
        i128 q1 = a / c, q2 = b / d;
        if (q1 == q2) {
            sum += q1;
            ++out_count;
            i128 na = c, nb = d, nc = a - q1 * c, nd = b - q1 * d;
            a = na; b = nb; c = nc; d = nd;
        } else {
            ll x = next_alpha();
            i128 na = a * x + b, nb = a, nc = c * x + d, nd = c;
            a = na; b = nb; c = nc; d = nd;
        }
    }

    cout << (ll)sum << "\n";
    return 0;
}
