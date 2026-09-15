#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    ll total = 0;

    for (int L = 1; L <= D; L++) {
        // Enumerate carry patterns C[0..L]
        // C[0]=0 (no carry into units)
        // C[i] ∈ {0,1} for i=0..L
        int max_pattern = 1 << (L + 1);
        int half = L / 2;
        int odd_len = L % 2;

        for (int pat = 0; pat < max_pattern; pat++) {
            // Extract C[0..L]
            int C[10]; // L ≤ 9, L+1 ≤ 10
            for (int i = 0; i <= L; i++) {
                C[i] = (pat >> i) & 1;
            }
            if (C[0] != 0) continue;

            bool valid = true;

            // Check carry pattern consistency for each digit pair
            // For pair i (0-indexed, i < half):
            //   C[i] == C[L-1-i] (parity constraint: both must be same)
            //   C[i+1] == C[L-i] (range constraint: carry out must match both sides)
            for (int i = 0; i < half; i++) {
                if (C[i] != C[L - 1 - i]) { valid = false; break; }
                if (C[i + 1] != C[L - i]) { valid = false; break; }
            }
            if (!valid) continue;

            // Middle (if odd length):
            // C[mid] must be 1 (2*a_mid + C[mid] odd → 2*a_mid even, so C[mid]=1)
            if (odd_len) {
                int mid = L / 2;
                if (C[mid] != 1) continue;
                // No C[mid+1] == C[mid] constraint — middle digit doesn't have
                // a symmetric pair counterpart like regular digit pairs do.
            }

            // Now count digit assignments for this carry pattern
            ll ways = 1;

            for (int i = 0; i < half; i++) {
                // Digit pair (d_i, d_{L-1-i})
                // Sum S = d_i + d_{L-1-i}
                // Constraint: S + C[i] ∈ [10*C[i+1], 10*C[i+1]+9]
                // And S + C[i] must be odd (from S + C[i] odd condition)
                int lo = 10 * C[i + 1] - C[i];
                int hi = 10 * C[i + 1] + 9 - C[i];
                if (lo < 0) lo = 0;
                if (hi > 18) hi = 18;
                
                // S must be in [lo, hi] and (S + C[i]) odd
                // Also, for outermost pair (i = half-1, which is the pair closest to the ends):
                // d_i and d_{L-1-i} must be non-zero
                bool is_outermost = (i == half - 1);
                
                ll cnt = 0;
                for (int S = lo; S <= hi; S++) {
                    if ((S + C[i]) % 2 == 0) continue; // must be odd
                    // Count ordered pairs (u,v) with u+v=S, 0≤u,v≤9
                    // u = d_i, v = d_{L-1-i}
                    int min_u = max(0, S - 9);
                    int max_u = min(9, S);
                    int pair_cnt = max_u - min_u + 1;
                    if (pair_cnt <= 0) continue;
                    
                    if (is_outermost) {
                        // No zero allowed at either end
                        // u=0 invalid, v=0 invalid → u≠0 and S-u≠0
                        // Count valid (u,v) where u∈[1,9], v∈[1,9], u+v=S
                        int valid_cnt = 0;
                        for (int u = max(1, S - 9); u <= min(9, S - 1); u++) {
                            valid_cnt++;
                        }
                        pair_cnt = valid_cnt;
                    }
                    cnt += pair_cnt;
                }
                
                if (cnt == 0) { valid = false; break; }
                ways *= cnt;
            }

            if (!valid) continue;

            // Middle digit (if odd length)
            if (odd_len) {
                int mid = L / 2;
                // 2*a_mid + C[mid] must be in [10*C[mid+1], 10*C[mid+1]+9]
                int lo = 10 * C[mid + 1];
                int hi = 10 * C[mid + 1] + 9;
                if (lo < 1) lo = 1; // 2*a_mid + 1 >= 1
                if (hi > 19) hi = 19; // 2*a_mid + 1 <= 19
                
                ll cnt = 0;
                // val = 2*a_mid + C[mid]; C[mid] is always 1 here
                // val must be odd (since C[mid]=1, 2*a_mid is even, sum is odd)
                for (int val = lo; val <= hi; val++) {
                    if (val % 2 == 0) continue; // must be odd
                    int a_mid = (val - C[mid]) / 2;
                    if (a_mid >= 0 && a_mid <= 9) cnt++;
                }
                
                if (cnt == 0) continue;
                ways *= cnt;
            }

            if (!valid) continue;
            total += ways;
        }
    }

    cout << total << "\n";
    return 0;
}
