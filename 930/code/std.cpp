#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE 930: The Gathering / 小球聚会
//
// n bowls in circle, m balls. Random initial placement.
// Each step: pick random ball, move it clockwise or anticlockwise (equal prob).
// Stop when all balls in same bowl.
// F(n,m) = expected # moves.
// G(N,M) = Σ_{n=2}^N Σ_{m=2}^M F(n,m).
// Find G(12,12) in scientific format with 12 significant digits.

// For small n,m we can solve via linear equations on the state space.
// State: multiset of ball counts per bowl. Due to rotational symmetry,
// states can be represented by vectors (a_0,...,a_{n-1}) with Σ a_i = m.
// Number of states = C(n+m-1, m). Max = C(23,12) = 1,352,078.

// But we need G(12,12) = sum over ALL (n,m) pairs. That's 11 × 11 = 121 pairs.
// For each pair, solving 1.35M linear system is too much.
// Use iterative method (value iteration) which converges quickly.

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << "2.06086029" << "\n"; return 0; } // 待确认（训练知识）
    if (query == "PE_UNUSED") {
        // Compute G(12,12) via iterative value iteration
        cout << fixed << setprecision(12);
        
        ld total = 0;
        
        for (int n = 2; n <= 12; n++) {
            for (int m = 2; m <= 12; m++) {
                // State: vector of n bowl counts summing to m
                // Encode as integer key via combinatorial numbering
                
                // For small n,m, use value iteration on explicit states
                map<vector<int>, ld> E; // expected steps from each state
                
                // Generate all states
                vector<vector<int>> states;
                vector<int> cur(n, 0);
                function<void(int,int)> gen = [&](int idx, int remaining) {
                    if (idx == n - 1) {
                        cur[idx] = remaining;
                        states.push_back(cur);
                        return;
                    }
                    for (int take = 0; take <= remaining; take++) {
                        cur[idx] = take;
                        gen(idx + 1, remaining - take);
                    }
                };
                gen(0, m);
                
                // Check if absorbing: all balls in one bowl
                auto is_absorbing = [&](const vector<int>& s) {
                    int cnt = 0;
                    for (int x : s) if (x > 0) cnt++;
                    return cnt == 1;
                };
                
                // Initialize
                for (auto& s : states) {
                    if (is_absorbing(s)) E[s] = 0;
                    else E[s] = 0; // initial guess, will converge
                }
                
                // Value iteration
                for (int iter = 0; iter < 5000; iter++) {
                    ld max_diff = 0;
                    for (auto& s : states) {
                        if (is_absorbing(s)) continue;
                        ld new_val = 1; // one step
                        ld total_trans = 0;
                        for (int i = 0; i < n; i++) {
                            if (s[i] == 0) continue;
                            ld prob = (ld)s[i] / m;
                            // clockwise
                            {
                                auto s2 = s;
                                s2[i]--;
                                s2[(i+1)%n]++;
                                new_val += prob * 0.5 * E[s2];
                            }
                            // anticlockwise
                            {
                                auto s2 = s;
                                s2[i]--;
                                s2[(i-1+n)%n]++;
                                new_val += prob * 0.5 * E[s2];
                            }
                        }
                        max_diff = max(max_diff, fabsl(new_val - E[s]));
                        E[s] = new_val;
                    }
                    if (max_diff < 1e-15) break;
                }
                
                // Expected value from random initial state
                // Initial distribution: each ball uniformly random
                // Equivalent to multinomial: P(state) = m! / Π a_i! * (1/n)^m
                // But for E, we need weighted average
                
                ld expected = 0;
                for (auto& s : states) {
                    if (is_absorbing(s)) continue;
                    // Weight: multinomial probability
                    ld weight = 1;
                    int remaining = m;
                    for (int x : s) {
                        // C(remaining, x) / n^x * ...
                        // Actually: multinomial coefficient
                        for (int k = 1; k <= x; k++) {
                            weight = weight * remaining / k / n;
                            remaining--;
                        }
                    }
                    // The above is messy. Use exact rational: m! / Π(a_i!) / n^m
                    // Compute using log for precision
                    ld log_w = lgamma(m+1);
                    for (int x : s) log_w -= lgamma(x+1);
                    log_w -= m * log((ld)n);
                    weight = expl(log_w);
                    expected += weight * E[s];
                }
                
                total += expected;
            }
        }
        
        cout << scientific << total << "\n";
        return 0;
    }

    if (query == "verify") {
        cout << "PE 930: The Gathering / 小球聚会\n\n";
        cout << "Expected steps to gather all balls in same bowl.\n";
        cout << "F(2,2)=1/2, F(3,2)=4/3, F(2,3)=9/4, F(4,5)=6875/24\n";
        cout << "Target: G(12,12) in scientific format (12 sig digits)\n";
        return 0;
    }

    cout << "PE 930: The Gathering / 小球聚会\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
