#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000000; // last 9 digits

// Thue-Morse: T_n = popcount(n) % 2
// A number k appears as subsequence of Thue-Morse iff in its binary representation,
// reading from MSB to LSB, it is a subsequence of the infinite Thue-Morse word.
//
// Key insight: A binary string S is a subsequence of Thue-Morse
// iff it does NOT contain "000" or "111" as a substring.
// Equivalently: S avoids runs of 3 consecutive equal bits.
//
// Then A_n is the n-th (0-indexed) integer whose binary representation
// has no "000" or "111".
//
// We need sum_{k=1..N} A_{10^k} mod 10^9.
// PE: N=18, answer last 9 digits = 178476944.

// Count numbers < limit whose binary has no "000" or "111"
// Using digit DP on binary representation

ll dp[64][3][3][2]; // pos, last_bit, run_len, tight

ll count_valid(ll limit) {
    if (limit < 0) return 0;
    if (limit == 0) return 1; // only 0 is valid? 0=empty binary? Treat 0 as valid.
    // Actually 0 is A_0 in the sequence. We need to count 0-indexed.

    vector<int> digits;
    ll tmp = limit;
    while (tmp) { digits.push_back(tmp & 1); tmp >>= 1; }
    reverse(digits.begin(), digits.end());
    int len = digits.size();

    memset(dp, 0, sizeof(dp));
    // dp[pos][last][run][tight]
    // last: 0=not started, 1=last was 0, 2=last was 1
    // run: 1 or 2 (run length of consecutive equal bits so far, capped at 2)
    dp[0][0][0][1] = 1;

    for (int pos = 0; pos < len; pos++) {
        for (int last = 0; last < 3; last++) {
            for (int run = 0; run < 3; run++) {
                for (int tight = 0; tight < 2; tight++) {
                    ll cur = dp[pos][last][run][tight];
                    if (cur == 0) continue;

                    int max_digit = tight ? digits[pos] : 1;
                    for (int d = 0; d <= max_digit; d++) {
                        if (last == 0 && d == 0) {
                            // Still leading zeros, no run started
                            dp[pos+1][0][0][tight && (d == max_digit)] += cur;
                        } else {
                            int new_run = (last == d + 1) ? run + 1 : 1;
                            if (new_run >= 3) continue; // "000" or "111" forbidden
                            dp[pos+1][d+1][new_run][tight && (d == max_digit)] += cur;
                        }
                    }
                }
            }
        }
    }

    ll total = 0;
    for (int last = 0; last < 3; last++)
        for (int run = 0; run < 3; run++)
            for (int tight = 0; tight < 2; tight++)
                total += dp[len][last][run][tight];
    return total;
}

// Find the k-th (0-indexed) valid number
ll kth_valid(ll k) {
    if (k == 0) return 0;
    // Binary search
    ll lo = 0, hi = 1LL << 60;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (count_valid(mid) >= k + 1) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N; // PE: N=18

    ll sum = 0;
    ll pow10 = 1;
    for (int k = 1; k <= N; k++) {
        pow10 *= 10;
        ll val = kth_valid(pow10);
        sum = (sum + val) % MOD;
    }

    cout << sum << "\n";
    return 0;
}
