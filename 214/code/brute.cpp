#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 214: Brute force - compute phi by factorization
// Only for small N (≤ 10^5)

int phi_brute(int n) {
    int res = n;
    int m = n;
    for (int d = 2; (ll)d * d <= m; d++) {
        if (m % d == 0) {
            res -= res / d;
            while (m % d == 0) m /= d;
        }
    }
    if (m > 1) res -= res / m;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L;
    cin >> N >> L;

    // Use simple primality test
    auto is_prime = [](int n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0) return false;
        for (int d = 3; (ll)d * d <= n; d += 2)
            if (n % d == 0) return false;
        return true;
    };

    // Memoize chain lengths
    unordered_map<int, int> memo;
    memo[1] = 1;
    function<int(int)> chain = [&](int n) -> int {
        if (memo.count(n)) return memo[n];
        return memo[n] = 1 + chain(phi_brute(n));
    };

    ll ans = 0;
    for (int n = 2; n < N; n++) {
        if (is_prime(n) && chain(n) == L) {
            ans += n;
        }
    }

    cout << ans << "\n";
}
