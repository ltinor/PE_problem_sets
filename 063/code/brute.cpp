#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// Compute a^n using big integer multiplication via __int128 or manual
// For our range, we can use __int128 if available, or use double
ull ipow(ull a, int n) {
    ull res = 1;
    for (int i = 0; i < n; i++) {
        // Check overflow
        if (res > ULLONG_MAX / a) return 0; // overflow
        res *= a;
    }
    return res;
}

int count_digits(ull x) {
    if (x == 0) return 1;
    int d = 0;
    while (x) { d++; x /= 10; }
    return d;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int x; cin >> x;  // ignore

    int ans = 0;
    for (int a = 1; a <= 9; a++) {
        for (int n = 1; n <= 25; n++) {
            // a^n with brute force - we need big integers
            // Use Python-style approach: count digits via log
            // Or track value with double for digit count check
            // Actually: a^n has n digits iff 10^(n-1) <= a^n < 10^n
            // We can check with double
            double val = n * log10((double)a);
            if (val >= n - 1 - 1e-12 && val < n - 1e-12) {
                ans++;
            }
        }
    }
    cout << ans << "\n";
}
