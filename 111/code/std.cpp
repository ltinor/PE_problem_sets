#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool is_prime(ll x) {
    if (x < 2) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;
    for (ll i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}

// S(n, d): sum of n-digit primes with max repeated digit d
ll S(int n, int d) {
    for (int k = n - 1; k >= 1; k--) {
        ll sum_val = 0;
        int non_d = n - k;

        // recursive enumeration: build n-digit number with exactly k d's
        function<void(int, int, ll)> dfs = [&](int pos, int cnt_d, ll cur) {
            if (pos == n) {
                if (cnt_d == k && cur >= (ll)pow(10, n-1) && is_prime(cur)) {
                    sum_val += cur;
                }
                return;
            }
            int remaining = n - pos;
            int needed_d = k - cnt_d;
            int non_d_used = pos - cnt_d;
            int non_d_needed = non_d - non_d_used;

            // Option: place digit d
            if (needed_d > 0 && needed_d <= remaining && !(pos == 0 && d == 0)) {
                dfs(pos + 1, cnt_d + 1, cur * 10 + d);
            }
            // Option: place a non-d digit
            if (non_d_needed > 0) {
                int start = (pos == 0) ? 1 : 0;
                for (int dig = start; dig <= 9; dig++) {
                    if (dig == d) continue;
                    dfs(pos + 1, cnt_d, cur * 10 + dig);
                }
            }
        };

        dfs(0, 0, 0);
        if (sum_val > 0) return sum_val;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    ll ans = 0;
    for (int d = 0; d <= 9; d++) {
        ans += S(n, d);
    }
    cout << ans << "\n";
    return 0;
}
