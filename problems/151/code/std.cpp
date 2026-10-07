#include<bits/stdc++.h>
using namespace std;

#define ll long long

// PE 151: Paper Sheets Expected Value
// After first batch, envelope has: 1*A2, 1*A3, 1*A4, 1*A5
// For next 14 batches (2-15): pick random sheet, cut if needed
// Count expected times envelope has exactly 1 sheet

// State: (a2, a3, a4, a5) counts of each size
// Max possible counts are limited (total sheets ≤ 5 typically)

struct State {
    int a2, a3, a4, a5;
    bool operator<(const State& o) const {
        if (a2 != o.a2) return a2 < o.a2;
        if (a3 != o.a3) return a3 < o.a3;
        if (a4 != o.a4) return a4 < o.a4;
        return a5 < o.a5;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Read dummy input (fixed-answer problem)
    int dummy;
    cin >> dummy;
    
    // Use iterative DP: prob[state] = probability of being in that state
    map<State, double> prob;
    prob[{1, 1, 1, 1}] = 1.0;
    
    double ans = 0.0;
    
    // 14 middle batches (batch 2 through 15)
    for (int step = 0; step < 14; step++) {
        map<State, double> next_prob;
        
        for (auto& [st, p] : prob) {
            if (p < 1e-15) continue;
            
            int total = st.a2 + st.a3 + st.a4 + st.a5;
            
            // Count if exactly 1 sheet
            if (total == 1) {
                ans += p;
            }
            
            // Cannot continue if no sheets (shouldn't happen)
            if (total == 0) continue;
            
            // Pick A2
            if (st.a2 > 0) {
                double pick_prob = (double)st.a2 / total;
                State ns = {st.a2 - 1, st.a3 + 1, st.a4 + 1, st.a5 + 1};
                next_prob[ns] += p * pick_prob;
            }
            
            // Pick A3
            if (st.a3 > 0) {
                double pick_prob = (double)st.a3 / total;
                State ns = {st.a2, st.a3 - 1, st.a4 + 1, st.a5 + 1};
                next_prob[ns] += p * pick_prob;
            }
            
            // Pick A4
            if (st.a4 > 0) {
                double pick_prob = (double)st.a4 / total;
                State ns = {st.a2, st.a3, st.a4 - 1, st.a5 + 1};
                next_prob[ns] += p * pick_prob;
            }
            
            // Pick A5
            if (st.a5 > 0) {
                double pick_prob = (double)st.a5 / total;
                State ns = {st.a2, st.a3, st.a4, st.a5 - 1};
                next_prob[ns] += p * pick_prob;
            }
        }
        
        prob = std::move(next_prob);
    }
    
    // After batch 15, the envelope has some state
    // We don't count batch 16 (last batch)
    
    cout << fixed << setprecision(6) << ans << "\n";
    return 0;
}
