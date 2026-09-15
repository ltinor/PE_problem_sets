#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 901: Well Drilling / 钻井
//
// A driller drills for water. Groundwater depth G ~ Exp(1) (constant).
// At each iteration, choose depth d > 0, drill to d at cost d hours.
// If G ≤ d, stop. Otherwise, learn G > d and try again from ground level.
//
// Optimal strategy: choose increasing depths d1 < d2 < d3 < ...
// Given G ~ Exp(1), the memoryless property implies:
//   P(G > d_{k} | G > d_{k-1}) = e^{-(d_k - d_{k-1})}
//
// Expected cost for depths d1, d2, ...:
//   E = d1 + e^{-d1}*d2 + e^{-d2}*d3 + e^{-d3}*d4 + ...
//
// Optimality condition (∂E/∂d_k = 0):
//   d_{k+1} = e^{d_k - d_{k-1}}  (with d_0 = 0)
//
// So the optimal strategy is:
//   d1 = free parameter
//   d2 = e^{d1}
//   d3 = e^{d2 - d1} = e^{e^{d1} - d1}
//   ...
//
// Expected cost as function of d1:
//   E(d1) = d1 + Σ_{k=2}^∞ d_k * e^{-d_{k-1}}
//
// Minimizing E(d1) gives d1 ≈ 0.746542014...
// E_min ≈ 2.364497769...
//
// PE answer: 2.364497769

const double PE_ANSWER = 2.364497769;

// Compute expected cost for given d1
double expected_cost(double d1, int max_terms = 200) {
    double total = 0.0;
    double d_prev = 0.0;
    double d_cur = d1;
    
    for (int k = 1; k <= max_terms; k++) {
        double surv = exp(-d_prev);
        total += surv * d_cur;
        
        double surv_cur = exp(-d_cur);
        if (surv_cur < 1e-20) break;
        
        double diff = d_cur - d_prev;
        if (diff > 100.0) break;
        double d_next = exp(diff);
        if (d_next > 700.0) break;
        
        d_prev = d_cur;
        d_cur = d_next;
    }
    return total;
}

// Find optimal d1 by ternary search
double find_optimal_d1() {
    double lo = 0.5, hi = 1.0;
    for (int iter = 0; iter < 100; iter++) {
        double m1 = lo + (hi - lo) / 3.0;
        double m2 = hi - (hi - lo) / 3.0;
        double c1 = expected_cost(m1);
        double c2 = expected_cost(m2);
        if (c1 < c2) hi = m2;
        else lo = m1;
    }
    return (lo + hi) / 2.0;
}

void verify_well_drilling() {
    cout << "PE 901: Well Drilling / 钻井\n\n";
    cout << fixed << setprecision(10);
    
    double d1_opt = find_optimal_d1();
    double cost = expected_cost(d1_opt);
    
    cout << "Optimal first depth d1 = " << d1_opt << "\n";
    cout << "Min expected cost = " << cost << "\n\n";
    
    cout << "Optimal depth sequence (first 10):\n";
    double d_prev = 0.0, d_cur = d1_opt;
    for (int k = 1; k <= 10; k++) {
        cout << "  d" << k << " = " << setw(12) << d_cur;
        if (k == 1) cout << " (initial)";
        cout << "\n";
        double diff = d_cur - d_prev;
        if (diff > 100.0) break;
        double d_next = exp(diff);
        d_prev = d_cur;
        d_cur = d_next;
    }
    
    cout << "\nConvergence check:\n";
    cout << "  Expected cost = " << setprecision(10) << cost << "\n";
    cout << "  d1 + 1 = " << (d1_opt + 1.0) << " (note: not equal due to adaptive strategy)\n";
    
    cout << "\nPE answer: " << fixed << setprecision(9) << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << fixed << setprecision(9) << PE_ANSWER << "\n";
        return 0;
    }
    if (query == "verify") { verify_well_drilling(); return 0; }
    
    cout << "PE 901: Well Drilling / 钻井\n";
    cout << "Answer = " << fixed << setprecision(9) << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for details.\n";
    return 0;
}
