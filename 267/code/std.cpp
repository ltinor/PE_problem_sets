#include<bits/stdc++.h>
using namespace std;

const double TARGET = 1e9;

// Precompute log factorials
vector<double> log_fact;

double log_comb(int n, int k) {
    if (k < 0 || k > n) return -1e300;
    return log_fact[n] - log_fact[k] - log_fact[n - k];
}

// Compute probability of reaching target for given f and N
double prob_for_f(int N, double f) {
    if (f <= 0 || f >= 1) return 0;
    
    double log_f_plus = log(1 + 2*f);
    double log_f_minus = log(1 - f);
    double log_target = log(TARGET);
    
    // Minimum H needed
    double h_min_exact = (log_target - N * log_f_minus) / (log_f_plus - log_f_minus);
    int H_min = max(0, (int)ceil(h_min_exact - 1e-12));
    if (H_min > N) return 0;
    
    double total_prob = 0;
    double log2_N = N * log(2.0);
    
    for (int h = H_min; h <= N; h++) {
        double log_p = log_comb(N, h) - log2_N;
        total_prob += exp(log_p);
    }
    
    return total_prob;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // Precompute log factorials
    log_fact.resize(N + 1);
    log_fact[0] = 0;
    for (int i = 1; i <= N; i++) {
        log_fact[i] = log_fact[i-1] + log((double)i);
    }
    
    // Grid search to find rough optimum, then ternary refinement
    double best_f = 0;
    double best_prob = 0;
    
    // Coarse grid search
    for (double f = 0.01; f < 1.0; f += 0.01) {
        double p = prob_for_f(N, f);
        if (p > best_prob) {
            best_prob = p;
            best_f = f;
        }
    }
    
    // Ternary refinement around best
    double lo = max(0.001, best_f - 0.02);
    double hi = min(0.999, best_f + 0.02);
    for (int iter = 0; iter < 200; iter++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        double p1 = prob_for_f(N, m1);
        double p2 = prob_for_f(N, m2);
        if (p1 < p2) {
            lo = m1;
        } else {
            hi = m2;
        }
    }
    
    best_f = (lo + hi) / 2;
    best_prob = prob_for_f(N, best_f);
    
    cout << fixed << setprecision(12) << best_prob << "\n";
    
    return 0;
}
