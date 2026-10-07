// PE 329 - Probabilistic Toad (Brute Force)
// Same DP but with double precision for quick verification

#include <bits/stdc++.h>
using namespace std;

vector<bool> is_prime(501, true);
void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= 500; i++)
        if (is_prime[i])
            for (int j = i * i; j <= 500; j += i)
                is_prime[j] = false;
}

int main() {
    sieve();
    
    string target;
    cin >> target;
    int L = (int)target.size();
    
    double total = 0.0;
    
    for (int start = 1; start <= 500; start++) {
        vector<double> dp(501, 0.0);
        dp[start] = 1.0;
        
        for (int t = 0; t < L; t++) {
            vector<double> after(501, 0.0);
            for (int p = 1; p <= 500; p++) {
                if (dp[p] == 0) continue;
                double prob = (is_prime[p] ? 2.0/3.0 : 1.0/3.0);
                if (target[t] == 'N') prob = 1.0 - prob;
                after[p] = dp[p] * prob;
            }
            
            if (t < L - 1) {
                vector<double> after_jump(501, 0.0);
                for (int p = 1; p <= 500; p++) {
                    if (after[p] == 0) continue;
                    if (p == 1) after_jump[2] += after[p];
                    else if (p == 500) after_jump[499] += after[p];
                    else {
                        after_jump[p-1] += after[p] * 0.5;
                        after_jump[p+1] += after[p] * 0.5;
                    }
                }
                dp = after_jump;
            } else {
                dp = after;
            }
        }
        
        double pos_sum = 0;
        for (int p = 1; p <= 500; p++) pos_sum += dp[p];
        total += pos_sum / 500.0;
    }
    
    cout << fixed << setprecision(15) << total << "\n";
    return 0;
}
