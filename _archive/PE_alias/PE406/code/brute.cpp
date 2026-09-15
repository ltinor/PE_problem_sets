#include<bits/stdc++.h>
using namespace std;

// PE406 brute: Guessing Game - brute force DP (same as std but clearly correct)
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    long long N, cost_lo, cost_hi;
    cin >> N >> cost_lo >> cost_hi;
    
    vector<double> E(N + 1, 0.0);
    E[0] = 0.0;
    E[1] = 0.0;
    
    for (int len = 2; len <= N; len++) {
        double best = 1e18;
        for (int k = 1; k <= len; k++) {
            double val = cost_lo * (k - 1) + cost_hi * (len - k)
                       + (k - 1) * E[k - 1] + (len - k) * E[len - k];
            val /= len;
            if (val < best) best = val;
        }
        E[len] = best;
    }
    
    double total = 0.0;
    for (int n = 1; n <= N; n++) {
        total += E[n];
    }
    
    cout << fixed << setprecision(6) << total << "\n";
}
