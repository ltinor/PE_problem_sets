#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Count entries in first R rows of Pascal's triangle not divisible by 7
// Use Lucas theorem: C(n,k) mod 7 ≠ 0 iff each base-7 digit of k ≤ corresponding digit of n
// Row n: count = Π(d_i + 1) where d_i are base-7 digits of n
// Sum over rows 0..R-1

ll count_row(ll n) {
    ll cnt = 1;
    while (n > 0) {
        cnt *= (n % 7 + 1);
        n /= 7;
    }
    return cnt;
}

// Efficient sum using base-7 decomposition
// Rows 0..R-1: split by base-7 representation
ll solve(ll R) {
    ll ans = 0;

    // Process in base-7
    vector<int> digits;
    ll tmp = R;
    while (tmp > 0) {
        digits.push_back(tmp % 7);
        tmp /= 7;
    }
    reverse(digits.begin(), digits.end());
    // Actually we want rows 0..R-1, so process R itself
    // But we can also use digit DP approach

    int d = digits.size();

    // Precompute triangular-like sums
    // For a block of 7^k consecutive rows starting at a multiple of 7^k:
    // The sum is 28^k (since sum of (d+1) for d=0..6 = 1+2+...+7 = 28)

    // Process digit by digit
    ll prefix = 0;  // accumulated prefix in original number
    ll sum_prefix = 0;  // sum of counts for rows 0..prefix*7^remaining-1

    for (int i = 0; i < d; i++) {
        int digit = digits[i];
        int remaining = d - i - 1;
        ll block_size = 1;
        for (int j = 0; j < remaining; j++) block_size *= 7;

        // For each possible digit value 0..digit-1 at this position
        for (int v = 0; v < digit; v++) {
            // This corresponds to a block of 7^remaining rows
            // starting at (prefix * 7 + v) * 7^remaining
            // In each of these rows, the count is count_row(row_num)
            // Sum over the block = (v+1) * 28^remaining
            // Actually: for a block of 7^k rows starting at multiple of 7^k,
            // the sum is 28^k

            // The digit at this position is v, all lower positions range 0..6
            // count_row for a number starting with (prefix*7+v) at position i
            // and lower digits free: contributes (v+1) for this digit
            // times Σ_{lower} count_row(lower) for 7^remaining rows

            // Sum over a full block of 7^k consecutive rows:
            ll block_sum = 1;
            for (int j = 0; j < remaining; j++) block_sum *= 28;
            ll contrib = (v + 1) * block_sum;
            ans += contrib;
        }

        // Now add the contribution of the exact prefix (digit itself)
        // For the prefix up to current position, each row has count
        // multiplied by (digit+1) for this digit
        // But the rows below are not full blocks; we process recursively

        // Actually simpler: let's track the running digit contribution
        // prefix accumulates the "fixed" part of count_row
        ll prefix_cnt = 1;
        // recalculate
        prefix_cnt = 1;
        ll p = 0;
        for (int j = 0; j <= i; j++) {
            prefix_cnt *= (digits[j] + 1);
            p = p * 7 + digits[j];
        }
        // No, this doesn't work well. Let me use a different approach.

        // Actually let me use the standard approach:
        // For R, decompose into base-7 digits. Process from most significant.
        // At each digit position, we add: Σ_{v=0}^{d-1} (v+1) * 28^{k}
        // where k is the remaining digits.
        // Then we proceed with the actual digit d.
    }

    // Reset and use cleaner approach
    ans = 0;
    ll pow7 = 1;
    ll pow28 = 1;

    // Process from least significant digit
    vector<int> digs;
    tmp = R;
    while (tmp > 0) {
        digs.push_back(tmp % 7);
        tmp /= 7;
    }
    // digs[0] is least significant

    // We'll use digit DP from most significant to least
    // Reuse digits vector from above
    // digits has most significant first

    return ans;
}

// Simpler approach: just iterate and sum (works for large R with base-7 grouping)
ll solve_fast(ll R) {
    // Use the formula: sum over rows 0..R-1 of Π(d_i+1)
    // Process recursively by base-7 representation

    ll ans = 0;

    // Generate all numbers < R and sum their row counts
    // But do it efficiently using base-7 block processing

    // Let f(R) = sum_{n=0}^{R-1} count_row(n)
    // If R = a * 7^k + b where 0 <= a < 7 and b < 7^k:
    // f(R) = a * 28^k + (a+1) * f(b)
    // Wait, this isn't quite right because the (a+1) factor multiplies ALL lower digits.

    // Let's think differently. For n written in base-7: n = d_{m-1}...d_1 d_0
    // count_row(n) = Π (d_i + 1)
    //
    // Sum over n = 0..R-1 can be done digit by digit:
    // Let g(k) = Σ_{n=0}^{7^k-1} count_row(n)
    // For k=0: g(0) = Σ_{n=0}^{0} count_row(0) = 1  -- wait, 0 has no digits, count=1
    // Actually count_row(0) = 1 (Π of empty set = 1)
    // g(0) = 1
    // For k=1: g(1) = Σ_{n=0}^{6} (n+1) = 1+2+...+7 = 28
    // For k=2: g(2) = Σ_{a=0}^{6} Σ_{n=0}^{7-1} (a+1) * count_row(n)
    //            = Σ_{a=0}^{6} (a+1) * g(1)
    //            = 28 * 28 = 28^2
    // Generally: g(k) = 28^k

    // Now for arbitrary R:
    // R = d_{m-1} * 7^{m-1} + d_{m-2} * 7^{m-2} + ... + d_0
    //
    // f(R) = Σ_{n=0}^{R-1} count_row(n)
    //
    // We can process from most significant digit:
    // For each position i (from most to least significant):
    //   Let d = digits[i], k = remaining digits after i
    //   For v = 0..d-1: add (v+1) * 28^k * (product of (digits[j]+1) for j < i)? No...

    // Actually the standard recursive formula:
    // f(R) where R = d * 7^k + rest:
    //   = Σ_{a=0}^{d-1} Σ_{b=0}^{7^k-1} count_row(a * 7^k + b) + Σ_{b=0}^{rest-1} count_row(d * 7^k + b)
    //   = Σ_{a=0}^{d-1} Σ_{b=0}^{7^k-1} (a+1) * count_row(b) + Σ_{b=0}^{rest-1} (d+1) * count_row(b)
    //   = Σ_{a=0}^{d-1} (a+1) * g(k) + (d+1) * f(rest)
    //   = d*(d+1)/2 * 28^k + (d+1) * f(rest)

    // So: f(R) = Σ over digits from MSB to LSB:
    //   For current digit d with k remaining digits:
    //   ans += d*(d+1)/2 * 28^k    (when we consider lower digits of this block fully)
    //   BUT the multiplier accumulates: each higher digit contributes (d_i+1) factor.

    // Actually, let me re-derive. Let R have base-7 digits: d_{m-1} d_{m-2} ... d_0

    // f(0) = 0
    // For R > 0, let R = d * 7^k + rest where d is MSB and rest < 7^k:
    // f(R) = d*(d+1)/2 * g(k) + (d+1) * f(rest)

    // Why? When the MSB is a (0 ≤ a < d), the count for each n = a*7^k + b is (a+1)*count_row(b).
    // Sum over b = 0..7^k-1 gives (a+1)*g(k). Sum over a = 0..d-1 gives (1+2+...+d)*g(k) = d(d+1)/2 * g(k).
    // When the MSB is exactly d, the count for n = d*7^k + b (b < rest) is (d+1)*count_row(b).
    // Sum over b = 0..rest-1 gives (d+1) * f(rest).

    // g(k) = 28^k

    // So we can compute f(R) recursively!

    vector<int> digits;
    ll tmp = R;
    while (tmp > 0) {
        digits.push_back(tmp % 7);
        tmp /= 7;
    }
    // digits[0] = least significant, digits[m-1] = most significant

    int m = digits.size();

    // Precompute powers of 28
    vector<ll> pow28(m + 1);
    pow28[0] = 1;
    for (int i = 1; i <= m; i++) {
        pow28[i] = pow28[i-1] * 28;
    }

    // Recursive function
    function<ll(ll, int)> f = [&](ll R, int k) -> ll {
        if (R == 0) return 0;
        if (k == 0) return 0;
        // k is the position index (0 = LSB)
        // In recursive calls, we process from MSB

        // Find the most significant digit
        // Actually let's use a different approach: process digit by digit from MSB

        return 0LL;
    };

    // Iterative approach processing from MSB to LSB:
    // Start with ans=0, multiplier=1
    // For each digit d at position k (from MSB, k = remaining lower digits):
    //   For v = 0..d-1: add multiplier * (v+1) * 28^k
    //   multiplier *= (d+1)
    // After processing all digits, we have sum for 0..R-1

    // Let's verify: for R=10 (base-7: 13, digits from LSB: [3,1])
    // m=2. Process from MSB: digit 1 at k=1, then digit 3 at k=0.
    //
    // Start: ans=0, mult=1
    // digit d=1, k=1:
    //   v=0: ans += 1 * (0+1) * 28^1 = 28
    //   mult *= (1+1) = 2
    // digit d=3, k=0:
    //   v=0: ans += 2 * 1 * 1 = 2
    //   v=1: ans += 2 * 2 * 1 = 4
    //   v=2: ans += 2 * 3 * 1 = 6
    //   mult *= (3+1) = 8
    // Total: 28+2+4+6 = 40
    //
    // Let's verify manually: rows 0-9 of Pascal's triangle, not divisible by 7:
    // Row 0: 1 → count=1 (not div by 7) 
    // Row 1: 1 1 → count=2
    // Row 2: 1 2 1 → count=3
    // Row 3: 1 3 3 1 → count=4
    // Row 4: 1 4 6 4 1 → count=5
    // Row 5: 1 5 10 10 5 1 → all not div by 7 → count=6
    // Row 6: 1 6 15 20 15 6 1 → count=7
    // Row 7: 1 7 21 35 35 21 7 1 → only 7 divisible by 7? 7%7=0, 21%7=0, 35%7=0.
    //   Non-divisible: 1,1 → count=2
    // Row 8: 1 8 28 56 70 56 28 8 1 → 28%7=0, 56%7=0, 70%7=0. 
    //   Non-divisible: 1,8=1, 1 → count=3? Wait, 8%7=1, so 1,8 mod 7 = 1. So 1,1,1 → 3.
    //   Actually C(8,0)=1, C(8,1)=8%7=1, C(8,2)=28%7=0, C(8,3)=56%7=0, C(8,4)=70%7=0,
    //   C(8,5)=56%7=0, C(8,6)=28%7=0, C(8,7)=8%7=1, C(8,8)=1. 
    //   count=1+1+1+1=4? Wait let me count: positions 0-8. 
    //   Not div by 7: positions 0,1,7,8 → count=4.
    // Row 9: 1 9 36 84 126 126 84 36 9 1
    //   9%7=2, 36%7=1, 84%7=0, 126%7=0
    //   Not div by 7: pos 0,1,2,7,8,9 → count=6
    //
    // Sum rows 0-9: 1+2+3+4+5+6+7+2+4+6 = 40. Correct!

    ans = 0;
    ll mult = 1;
    for (int i = m - 1; i >= 0; i--) {
        int d = digits[i];
        int k = i; // remaining lower digits

        // Sum v=0..d-1 of (v+1) = d*(d+1)/2
        ll sum_v = (ll)d * (d + 1) / 2;
        ans += mult * sum_v * pow28[k];

        mult *= (d + 1);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll R;
    cin >> R;

    cout << solve_fast(R) << "\n";
    return 0;
}
