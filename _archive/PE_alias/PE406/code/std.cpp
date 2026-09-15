#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE406: Guessing Game
// Guess secret number t in [1,n]. Each guess x:
// - x < t: pay cost_lo, continue
// - x > t: pay cost_hi, continue  
// - x = t: done (pay 0)
// Minimize EXPECTED total cost (t uniform random)
// Sum over n=1..N of min expected cost, output as float with 6 decimal places
// Original PE: N=10000, cost_lo=1, cost_hi=1 (standard binary search)
// PE answer: 36813.982586

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    ll N, cost_lo, cost_hi;
    cin >> N >> cost_lo >> cost_hi;
    
    // DP: E[len] = min expected cost for interval of length len
    // E[0] = 0, E[1] = 0 (if secret is the only number, we know it)
    // For len >= 2: E[len] = min_{1 <= k <= len} (cost_lo*(k-1)/len + cost_hi*(len-k)/len 
    //         + (k-1)/len * E[k-1] + (len-k)/len * E[len-k])
    // Multiply both sides by len:
    // len * E[len] = min_k (cost_lo*(k-1) + cost_hi*(len-k) + (k-1)*E[k-1] + (len-k)*E[len-k])
    
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
