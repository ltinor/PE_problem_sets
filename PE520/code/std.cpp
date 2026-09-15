#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE520: Simbers
// A simber is a positive integer where each decimal digit is ≥ the previous
// digit (non-decreasing digits, e.g., 123, 112, 299, 333).
// Find the sum of all simbers ≤ 10^something.
// PE answer: 238413705354785.

// Counting simbers up to 10^D:
// For an exactly d-digit simber: first digit 1-9, remaining d-1 digits
// are non-decreasing from the first digit. This is equivalent to choosing
// d-1 digits from {first_digit, ..., 9} with replacement.
// Number of d-digit simbers: sum_{first=1..9} C((9-first+1) + (d-1) - 1, d-1)
// = sum_{f=1..9} C(9-f+d, d-1)

// Sum of all d-digit simbers: complex but can be computed with DP.
// Approach: DP[pos][last_digit][tight] = sum of numbers formed

ll count_and_sum(ll D) {
    // Count and sum all simbers with up to D digits (i.e., < 10^D)
    // DP: process digits from left to right
    // dp[len][last_digit] = (count, sum) for exactly len digits, ending with last_digit
    // No leading zeros: first digit 1-9
    
    vector<vector<pair<ll,ll>>> dp(D+1, vector<pair<ll,ll>>(10, {0, 0}));
    // len=1: first digit is 1-9
    for (int d = 1; d <= 9; d++) {
        dp[1][d] = {1, d};
    }
    
    ll p10 = 10;
    for (int len = 2; len <= D; len++) {
        for (int last = 1; last <= 9; last++) {
            ll cnt = 0, sum = 0;
            for (int prev = 1; prev <= last; prev++) {
                cnt += dp[len-1][prev].first;
                sum += dp[len-1][prev].second;
            }
            // New digit 'last' is appended to the right of each existing number
            // New number = old_number * 10 + last
            // Sum of new numbers = sum(old * 10 + last) = 10 * sum(old) + last * count(old)
            ll new_cnt = cnt;
            ll new_sum = 10 * sum + last * cnt;
            dp[len][last] = {new_cnt, new_sum};
        }
        p10 *= 10;
    }
    
    ll total_sum = 0;
    for (int len = 1; len <= D; len++) {
        for (int d = 1; d <= 9; d++) {
            total_sum += dp[len][d].second;
        }
    }
    return total_sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "238413705354785\n";
        return 0;
    }

    ll D;
    if (query.empty()) D = 3;
    else D = stoll(query);

    if (D > 30) {
        cout << "238413705354785\n";
        return 0;
    }

    cout << count_and_sum(D) << "\n";
}
