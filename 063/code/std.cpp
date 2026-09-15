#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    // Read and ignore input
    int x; cin >> x;

    int ans = 0;
    // For base a from 1 to 9, count how many n make a^n have exactly n digits
    // a^n has n digits when 10^(n-1) <= a^n < 10^n
    // Taking log10: n-1 <= n*log10(a) < n
    // So n-1 <= n*log10(a) => n*(1 - log10(a)) <= 1 => n <= 1/(1-log10(a))
    // And n*log10(a) < n always true for a<10
    // Also n >= 1
    for (int a = 1; a <= 9; a++) {
        double loga = log10((double)a);
        // Maximum n such that n*log10(a) >= n-1
        // n*(1 - loga) <= 1 => n <= 1/(1-loga)
        int max_n = (int)floor(1.0 / (1.0 - loga));
        // But we also need n >= 1 and a^n to have exactly n digits
        // Actually, check directly: a^n has n digits => 10^(n-1) <= a^n < 10^n
        // This means n-1 <= n*log10(a) < n
        // Upper bound: n*log10(a) < n => log10(a) < 1 => a < 10, always true for a<=9
        // Lower bound: n*log10(a) >= n-1 => n <= 1/(1-log10(a))
        for (int n = 1; n <= max_n + 2; n++) {
            // Verify with big integer or use the formula
            // n-digit number: 10^(n-1) <= a^n < 10^n
            // => n-1 <= n*log10(a) < n
            double low = n * loga;
            if (low >= n - 1 - 1e-12 && low < n - 1e-12) {
                ans++;
            }
        }
    }
    cout << ans << "\n";
}
