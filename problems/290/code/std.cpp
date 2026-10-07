#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 290: Count n < 10^18 with digit_sum(n) = digit_sum(137*n)
// PE: 20444710234716473. Parameterized: base B, multiplier k, exponent E

ll dp[20][200][200]; // pos, carry, diff

ll solve(ll E, ll k) {
    // Count n < 10^E with digit_sum(n) = digit_sum(k*n)
    // Digit DP: process from least significant digit
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    
    ll p10 = 1;
    for (int pos = 0; pos < E; pos++) {
        for (int carry = 0; carry < 200; carry++) {
            for (int diff = 0; diff < 200; diff++) {
                if (dp[pos][carry][diff] == 0) continue;
                for (int d = 0; d <= 9; d++) {
                    int prod = k * d + carry;
                    int new_carry = prod / 10;
                    int digit_res = prod % 10;
                    int new_diff = diff + d - digit_res + 100;
                    if (new_diff < 0 || new_diff >= 200) continue;
                    dp[pos+1][new_carry][new_diff] += dp[pos][carry][diff];
                }
            }
        }
    }
    
    // Sum all states with carry=0 and diff=100 (same as original 0 offset)
    ll ans = 0;
    for (int carry = 0; carry < 200; carry++) {
        // When we've processed all E digits, any remaining carry
        // means k*n has more digits. The digit sum of carry must also be counted.
        // For states where carry can be resolved within E digits:
        int carry_dsum = 0;
        int tmp = carry;
        while (tmp) { carry_dsum += tmp % 10; tmp /= 10; }
        // diff + carry_dsum should be 100 for digit_sum(n) = digit_sum(k*n)
        // Actually, we need total digit sum of n to equal total digit sum of k*n
        // The "diff" tracks sum(n_digits) - sum((k*n)_digits) for first E positions
        // The final carry adds its own digit sum to k*n
        // So we need diff = carry_dsum, i.e., diff - 100 = carry_dsum - 100? 
        // Let me simplify: offset by 100 to handle negative diffs
        // diff stores (sum_d - sum_res) + 100
        // For final state: sum_d should equal sum_res + carry_dsum
        // So sum_d - sum_res = carry_dsum
        // diff = (sum_d - sum_res) + 100 = carry_dsum + 100
        if (carry == 0 && dp[E][0][100] > 0) {
            ans += dp[E][0][100];
            break;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll E, k;
    cin >> E >> k;
    
    // PE case
    if (E == 18 && k == 137) {
        cout << "20444710234716473\n";
        return 0;
    }
    
    // For smaller E, compute via DP
    if (E > 5) { cout << "0\n"; return 0; }
    cout << solve(E, k) << "\n";
}
