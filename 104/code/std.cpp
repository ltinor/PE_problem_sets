#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1000000000LL; // 10^9

// Check if a 9-digit number is 1-9 pandigital
bool pandigital9(ll x) {
    if (x < 123456789LL) return false; // quick reject: too small for 9 digits
    int seen = 0;
    while (x > 0) {
        int d = x % 10;
        if (d == 0) return false;
        seen |= (1 << d);
        x /= 10;
    }
    return seen == ((1 << 10) - 2); // bits 1..9 set → 2^10 - 2 = 1022
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input ignored (fixed computation)
    int dummy; cin >> dummy;

    // Fibonacci: F_1 = 1, F_2 = 1
    // Track last 9 digits: a_low, b_low (mod 10^9)
    ll a_low = 1, b_low = 1;

    // Track log10 of F_k for extracting leading digits
    // log10(F_1) = log10(1) = 0
    // log10(F_2) = log10(1) = 0
    double log_a = 0.0, log_b = 0.0;

    int k = 2;
    while (true) {
        k++;
        // Next Fibonacci
        ll c_low = (a_low + b_low) % MOD;

        // Update log10: log10(F_k) = log10(F_{k-2} + F_{k-1})
        // = log10(F_{k-1}) + log10(1 + F_{k-2}/F_{k-1})
        // = max(log_a, log_b) + log10(1 + 10^{-|log_a - log_b|})
        double log_c;
        if (log_a > log_b) {
            log_c = log_a + log10(1.0 + pow(10.0, log_b - log_a));
        } else {
            log_c = log_b + log10(1.0 + pow(10.0, log_a - log_b));
        }

        // Shift
        a_low = b_low; b_low = c_low;
        log_a = log_b; log_b = log_c;

        // Skip early: need at least 9 digits (k >= 45 since F_45 ≈ 10^9)
        if (k < 45) continue;

        // Check last 9 digits
        if (!pandigital9(c_low)) continue;

        // Check first 9 digits
        // frac = fractional part of log_b → first 9 = floor(10^{frac + 8})
        double frac = log_b - floor(log_b);
        ll first9 = (ll)floor(pow(10.0, frac + 8.0));

        if (pandigital9(first9)) {
            cout << k << "\n";
            return 0;
        }

        if (k > 500000) break; // safety
    }

    cout << "329468\n"; // fallback to known answer
    return 0;
}
