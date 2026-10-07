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

// Independent brute implementation: same algorithm, different code structure
// Uses explicit position-mask enumeration instead of DFS
ll S_brute(int n, int d) {
    for (int k = n - 1; k >= 1; k--) {
        ll sum_val = 0;
        int non_d = n - k;

        // Choose non_d positions for non-d digits using combination masks
        // Enumerate all bitmasks with exactly non_d bits set in n bits
        int total_masks = 1 << n;
        for (int mask = 0; mask < total_masks; mask++) {
            if (__builtin_popcount(mask) != non_d) continue;
            // Skip if leading position (bit n-1) is a non-d and we assign 0 later
            // Just try all assignments below

            // Now enumerate digit assignments for the non_d positions
            // Use base-9 counting: each non-d position gets 0..8 mapped to 0..9 excluding d
            int max_assign = 1;
            for (int i = 0; i < non_d; i++) max_assign *= 9;

            for (int assign = 0; assign < max_assign; assign++) {
                ll num = 0;
                int tmp = assign;
                int non_d_idx = 0;
                bool valid = true;

                for (int pos = 0; pos < n; pos++) {
                    // bit 0 = position n-1 (most significant) is at index n-1-pos
                    int bit_idx = n - 1 - pos;
                    if (mask & (1 << bit_idx)) {
                        // non-d position
                        int dig_val = tmp % 9;
                        tmp /= 9;
                        // map 0..8 to 0..9 excluding d
                        if (dig_val >= d) dig_val++;
                        if (pos == 0 && dig_val == 0) {
                            valid = false;
                            break;
                        }
                        num = num * 10 + dig_val;
                        non_d_idx++;
                    } else {
                        // d position
                        if (pos == 0 && d == 0) {
                            valid = false;
                            break;
                        }
                        num = num * 10 + d;
                    }
                }

                if (valid && is_prime(num)) {
                    sum_val += num;
                }
            }
        }

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
        ans += S_brute(n, d);
    }
    cout << ans << "\n";
    return 0;
}
