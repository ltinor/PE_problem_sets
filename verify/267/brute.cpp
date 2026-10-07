#include<bits/stdc++.h>
using namespace std;

const double TARGET = 1e9;

double prob_for_f_exact(int N, double f) {
    if (f <= 0 || f >= 1) return 0;
    
    int H_min = 0;
    // Find min H such that (1+2f)^H * (1-f)^(N-H) >= TARGET
    for (int h = 0; h <= N; h++) {
        double capital = pow(1 + 2*f, h) * pow(1 - f, N - h);
        if (capital >= TARGET - 1e-9) {
            H_min = h;
            break;
        }
        if (h == N) return 0; // can't reach target
    }
    
    // Compute exact binomial probability
    double total = 0;
    for (int h = H_min; h <= N; h++) {
        // C(N,h) / 2^N
        double comb = 1.0;
        for (int i = 1; i <= h; i++) {
            comb = comb * (N - i + 1) / i;
        }
        total += comb / pow(2.0, N);
    }
    
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    double best = 0;
    // Brute-force search over f
    for (double f = 0.001; f < 1.0; f += 0.001) {
        double p = prob_for_f_exact(N, f);
        if (p > best) best = p;
    }
    
    cout << fixed << setprecision(12) << best << "\n";
    
    return 0;
}
