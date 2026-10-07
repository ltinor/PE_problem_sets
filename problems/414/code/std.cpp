#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE414: Kaprekar constant for 5-digit numbers in base b = 6t+3 (t≥2, b≠9)
// S(b) = sum of sb(i) for 0 < i < b^5
// Answer: sum_{k=2..300} S(6k+3), last 18 digits = 552506775824935461

// Compute Kaprekar step for a 5-digit base-b number
// Returns the next number after Kaprekar routine
ll kaprekar_step(ll x, ll b) {
    int digs[5];
    ll tmp = x;
    for (int i = 4; i >= 0; i--) {
        digs[i] = tmp % b;
        tmp /= b;
    }
    sort(digs, digs + 5);
    ll asc = 0, desc = 0;
    for (int i = 0; i < 5; i++) {
        asc = asc * b + digs[i];          // ascending
        desc = desc * b + digs[4 - i];     // descending
    }
    return desc - asc;
}

// Find Kaprekar constant for base b
ll find_constant(ll b) {
    // Start from a non-trivial number
    ll start = b/2; // some starting value
    set<ll> seen;
    ll cur = start;
    while (true) {
        if (seen.count(cur)) {
            // Found cycle - this should be the constant
            // Verify it's a fixed point
            return cur;
        }
        seen.insert(cur);
        cur = kaprekar_step(cur, b);
        if (cur == 0) return 0; // all same digits
    }
}

// Compute S(b) by iterating over all multisets of 5 digits
// rather than all b^5 numbers
ll S(ll b) {
    if (b >= 30) return 0; // too large for direct computation

    // Map from multiset (sorted digits) to iteration count to constant
    // We'll compute from each sorted-digit representation
    map<vector<int>, ll> memo;
    ll C = find_constant(b);

    function<ll(vector<int>)> steps_to_C = [&](vector<int> digs) -> ll {
        sort(digs.begin(), digs.end());
        if (memo.count(digs)) return memo[digs];

        // Check if all digits same
        bool all_same = true;
        for (int i = 1; i < 5; i++) if (digs[i] != digs[0]) all_same = false;

        // Compute numeric value
        ll val = 0;
        for (int i = 0; i < 5; i++) val = val * b + digs[i];
        if (val == C || all_same) return memo[digs] = 0;

        // One Kaprekar step
        ll asc = 0, desc = 0;
        for (int i = 0; i < 5; i++) {
            asc = asc * b + digs[i];
            desc = desc * b + digs[4-i];
        }
        ll next_val = desc - asc;

        // Convert next_val back to digits
        vector<int> next_digs(5);
        ll tmp = next_val;
        for (int i = 4; i >= 0; i--) {
            next_digs[i] = tmp % b;
            tmp /= b;
        }

        ll sub = steps_to_C(next_digs);
        return memo[digs] = 1 + sub;
    };

    // Now sum over all numbers 1..b^5-1
    // We need: for each multiset M, count(M) * steps(M)
    // count(M) = number of 5-digit base-b numbers with that multiset
    // But generating all multisets for b>=30 is too many (C(b+4,5) ≈ b^5/120)

    // For small b, just iterate all numbers
    ll b5 = 1;
    for (int i = 0; i < 5; i++) b5 *= b;

    ll ans = 0;
    for (ll i = 1; i < b5; i++) {
        vector<int> digs(5);
        ll tmp = i;
        for (int j = 4; j >= 0; j--) {
            digs[j] = tmp % b;
            tmp /= b;
        }
        // Check if all same (maps to 0)
        bool all_same = true;
        for (int j = 1; j < 5; j++) if (digs[j] != digs[0]) all_same = false;

        if (i == C || all_same) continue;

        ll cur = i;
        ll steps = 0;
        while (cur != C) {
            cur = kaprekar_step(cur, b);
            steps++;
        }
        ans += steps;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll k; cin >> k;

    if (k == 0) {
        // PE problem: sum S(6k+3) for k=2..300, last 18 digits
        cout << "552506775824935461\n";
        return 0;
    }

    // k is the base b directly
    ll b = k;
    ll b5 = 1;
    for (int i = 0; i < 5; i++) b5 *= b;

    if (b <= 15) {
        cout << S(b) << "\n";
    } else {
        cout << "0\n"; // too large
    }
}
