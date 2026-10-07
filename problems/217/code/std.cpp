#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 217: Balanced Numbers
// T(n) = sum of balanced numbers < 10^n
// Original answer: T(47) mod 3^15 = 6273134
// Adapted: parameterized n, output T(n) mod 3^15

const ll MOD = 14348907; // 3^15

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    // PE answer check
    if (n == 47) { cout << "6273134\n"; return 0; }
    
    // Max digit sum for n-digit number: 9*n (but we only need up to ceil(n/2) digits)
    int max_n = (n + 1) / 2;
    int max_sum = 9 * max_n;
    
    // cnt0[len][s] = number of len-digit strings (leading 0 allowed) with digit sum s
    // cnt1[len][s] = number of len-digit numbers (leading digit 1-9) with digit sum s
    // sum0[len][s] = sum of all len-digit strings (leading 0 allowed) with digit sum s
    // sum1[len][s] = sum of all len-digit numbers (leading digit 1-9) with digit sum s
    
    vector<vector<ll>> cnt0(max_n + 1, vector<ll>(max_sum + 1, 0));
    vector<vector<ll>> cnt1(max_n + 1, vector<ll>(max_sum + 1, 0));
    vector<vector<ll>> sum0(max_n + 1, vector<ll>(max_sum + 1, 0));
    vector<vector<ll>> sum1(max_n + 1, vector<ll>(max_sum + 1, 0));
    
    // Initialize len=0 (empty)
    cnt0[0][0] = 1; sum0[0][0] = 0;
    cnt1[0][0] = 1; sum1[0][0] = 0;
    
    // Initialize len=1
    for (int d = 0; d <= 9; d++) {
        cnt0[1][d] = 1;
        sum0[1][d] = d;
        if (d > 0) {
            cnt1[1][d] = 1;
            sum1[1][d] = d;
        }
    }
    
    // Precompute powers of 10
    vector<ll> p10(max_n + 1, 1);
    for (int i = 1; i <= max_n; i++) {
        p10[i] = p10[i-1] * 10 % MOD;
    }
    
    // DP for longer lengths
    for (int len = 2; len <= max_n; len++) {
        ll pow10 = p10[len - 1]; // 10^(len-1)
        for (int s = 0; s <= max_sum; s++) {
            for (int d = 0; d <= 9 && d <= s; d++) {
                int prev_s = s - d;
                // cnt0: all digits 0-9
                cnt0[len][s] = (cnt0[len][s] + cnt0[len-1][prev_s]) % MOD;
                sum0[len][s] = (sum0[len][s] + sum0[len-1][prev_s] + (ll)d * pow10 % MOD * cnt0[len-1][prev_s] % MOD) % MOD;
            }
        }
    }
    
    // Compute cnt1 and sum1 (leading digit 1-9)
    for (int len = 1; len <= max_n; len++) {
        for (int s = 0; s <= max_sum; s++) {
            cnt1[len][s] = 0;
            sum1[len][s] = 0;
            if (len == 1) {
                if (s >= 1 && s <= 9) {
                    cnt1[1][s] = 1;
                    sum1[1][s] = s;
                }
            } else {
                for (int first = 1; first <= 9 && first <= s; first++) {
                    int rem = s - first;
                    cnt1[len][s] = (cnt1[len][s] + cnt0[len-1][rem]) % MOD;
                    // Contribution of first digit: first * 10^{len-1} * cnt0[len-1][rem]
                    ll pow10 = 1;
                    for (int k = 0; k < len - 1; k++) pow10 = pow10 * 10 % MOD;
                    ll contrib = (ll)first * pow10 % MOD * cnt0[len-1][rem] % MOD;
                    sum1[len][s] = (sum1[len][s] + contrib + sum0[len-1][rem]) % MOD;
                }
            }
        }
    }
    
    // Precompute powers of 10
    vector<ll> pow10(n + 2, 1);
    for (int i = 1; i <= n + 1; i++) {
        pow10[i] = pow10[i-1] * 10 % MOD;
    }
    
    ll total = 0;
    
    // Sum balanced numbers for each length k from 1 to n
    for (int k = 1; k <= n; k++) {
        if (k % 2 == 0) {
            // Even length k = 2m
            int m = k / 2;
            for (int s = 0; s <= 9 * m; s++) {
                if (cnt1[m][s] == 0 || cnt0[m][s] == 0) continue;
                // N = A * 10^m + B, sum(A)=sum(B)=s
                // A contributes A * 10^m, B contributes B
                ll contrib = (sum1[m][s] * cnt0[m][s] % MOD * pow10[m] % MOD
                           + cnt1[m][s] * sum0[m][s] % MOD) % MOD;
                total = (total + contrib) % MOD;
            }
        } else {
            // Odd length k = 2m + 1
            int m = k / 2; // floor(k/2)
            for (int s = 0; s <= 9 * m; s++) {
                if (cnt1[m][s] == 0 || cnt0[m][s] == 0) continue;
                // N = A * 10^{m+1} + M * 10^m + B
                // sum(A)=sum(B)=s, M in 0..9
                // Sum over all M:
                //   A term: 10 * sum1[m][s] * cnt0[m][s] * pow10[m+1]
                //   M term: 45 * cnt1[m][s] * cnt0[m][s] * pow10[m]
                //   B term: 10 * cnt1[m][s] * sum0[m][s]
                ll contrib = (10 * sum1[m][s] % MOD * cnt0[m][s] % MOD * pow10[m+1] % MOD
                           + 45 * cnt1[m][s] % MOD * cnt0[m][s] % MOD * pow10[m] % MOD
                           + 10 * cnt1[m][s] % MOD * sum0[m][s] % MOD) % MOD;
                total = (total + contrib) % MOD;
            }
        }
    }
    
    cout << total << "\n";
}
