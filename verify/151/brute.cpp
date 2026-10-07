#include<bits/stdc++.h>
using namespace std;

// Brute force: same DP as std, just simpler for verification
// PE 151: Expected value of finding single sheet in envelope

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
    
    int dummy;
    cin >> dummy;
    
    map<State, double> prob;
    prob[{1, 1, 1, 1}] = 1.0;
    
    double ans = 0.0;
    
    for (int step = 0; step < 14; step++) {
        map<State, double> next_prob;
        
        for (auto& [st, p] : prob) {
            int total = st.a2 + st.a3 + st.a4 + st.a5;
            
            if (total == 1) ans += p;
            if (total == 0) continue;
            
            if (st.a2 > 0) {
                next_prob[{st.a2-1, st.a3+1, st.a4+1, st.a5+1}] += p * st.a2 / total;
            }
            if (st.a3 > 0) {
                next_prob[{st.a2, st.a3-1, st.a4+1, st.a5+1}] += p * st.a3 / total;
            }
            if (st.a4 > 0) {
                next_prob[{st.a2, st.a3, st.a4-1, st.a5+1}] += p * st.a4 / total;
            }
            if (st.a5 > 0) {
                next_prob[{st.a2, st.a3, st.a4, st.a5-1}] += p * st.a5 / total;
            }
        }
        
        prob = std::move(next_prob);
    }
    
    cout << fixed << setprecision(6) << ans << "\n";
    return 0;
}
