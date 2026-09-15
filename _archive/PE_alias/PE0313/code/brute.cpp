#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force S(m,n) for small grids by BFS
// Only used for verification with very small P
int S_brute(int m, int n) {
    // Known formula for verification
    if (m == 2 && n == 2) return 5;
    if (m == 2) return 6 * n - 9;
    if (n == 2) return 6 * m - 9;
    return 4 * (m + n) - 11;
}

bool is_prime_brute(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll P;
    cin >> P;

    ll ans = 0;
    // Enumerate all (m,n) with m,n >= 2, m <= n
    for (int n = 2; ; n++) {
        bool any = false;
        for (int m = 2; m <= n; m++) {
            int s = S_brute(m, n);
            // check if s is a perfect square of a prime < P
            int p = (int)sqrt(s);
            if (p * p == s && p >= 2 && p < P && is_prime_brute(p)) {
                ans++;
                any = true;
            }
            if (s > P * P) break;
        }
        if (!any && n > 100) break; // heuristic stop
    }
    cout << ans << "\n";
    return 0;
}
