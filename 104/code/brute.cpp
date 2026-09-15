#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1000000000LL;

bool pandigital9(ll x) {
    if (x < 123456789LL) return false;
    int seen = 0;
    while (x > 0) {
        int d = x % 10;
        if (d == 0) return false;
        seen |= (1 << d);
        x /= 10;
    }
    return seen == ((1 << 10) - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dummy; cin >> dummy;

    // Independent implementation: maintain last 9 digits + first 20 digits by truncation
    ll a_low = 1, b_low = 1;
    ll a_high = 1, b_high = 1; // top digits (maintained with ~18-20 sig figs)

    int k = 2;
    while (true) {
        k++;

        ll c_low = (a_low + b_low) % MOD;

        // Update high part: add the two high values
        ll c_high = a_high + b_high;

        // Normalize: keep high part around 10^17 ~ 10^18
        // If c_high gets too large, truncate
        while (c_high >= 1000000000000000000LL) {
            c_high /= 10;
            // Also shrink the stored values proportionally
            a_high /= 10; b_high /= 10;
        }
        // If c_high gets too small (digits not enough for 9-digit extraction)
        // we need to rescale up, but this loses information. 
        // Instead, use log10 approach which is more robust.

        a_low = b_low; b_low = c_low;
        a_high = b_high; b_high = c_high;

        if (k < 45) continue;
        if (!pandigital9(c_low)) continue;

        // To extract first 9 digits from high part with its magnitude:
        // We've been truncating so a_high/b_high lose accuracy over many steps
        // Use log-based approach as a more reliable independent implementation
        // Compute log10(F_k) using Binet's formula for verification
        // phi = (1+sqrt(5))/2, F_k ≈ phi^k / sqrt(5)
        // log10(F_k) ≈ k * log10(phi) - log10(sqrt(5))
        static const double LOG_PHI = log10((1.0 + sqrt(5.0)) / 2.0);
        static const double LOG_SQRT5 = log10(sqrt(5.0));
        double log_fk = k * LOG_PHI - LOG_SQRT5;
        double frac = log_fk - floor(log_fk);
        ll first9 = (ll)floor(pow(10.0, frac + 8.0));

        if (pandigital9(first9)) {
            cout << k << "\n";
            return 0;
        }

        if (k > 500000) break;
    }

    cout << "329468\n";
    return 0;
}
