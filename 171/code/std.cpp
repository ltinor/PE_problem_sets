#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 1000000000;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    if(D <= 0 || D > 20) return 1;

    int MAX_SUM = D * 81; // 9*9*D

    // dp[sum] = count, sum_val[sum] = total sum of numbers (as built from MSB to LSB)
    vector<ll> dp(MAX_SUM + 1, 0);
    vector<ll> sum_val(MAX_SUM + 1, 0);

    dp[0] = 1; // empty string
    sum_val[0] = 0;

    for(int len = 1; len <= D; len++){
        vector<ll> ndp(MAX_SUM + 1, 0);
        vector<ll> nsum(MAX_SUM + 1, 0);
        for(int s = 0; s <= MAX_SUM; s++){
            if(dp[s] == 0 && sum_val[s] == 0) continue;
            for(int d = 0; d <= 9; d++){
                int ns = s + d * d;
                if(ns > MAX_SUM) continue;
                ndp[ns] = (ndp[ns] + dp[s]) % MOD;
                nsum[ns] = (nsum[ns] + sum_val[s] * 10 + d * dp[s]) % MOD;
            }
        }
        dp = ndp;
        sum_val = nsum;
    }

    // Find all perfect squares <= MAX_SUM
    vector<int> squares;
    for(int i = 1; i * i <= MAX_SUM; i++){
        squares.push_back(i * i);
    }

    // pow10[l] = 10^l mod MOD
    vector<ll> pow10(D + 1, 1);
    for(int i = 1; i <= D; i++){
        pow10[i] = pow10[i-1] * 10 % MOD;
    }

    ll total = 0;

    // For each exact length L from 1 to D
    // We recompute DP for each length to get dp[L-1] and sum_val[L-1]
    // Actually, let's do it incrementally

    // Reset DP and build up length by length
    dp.assign(MAX_SUM + 1, 0);
    sum_val.assign(MAX_SUM + 1, 0);
    dp[0] = 1;
    sum_val[0] = 0;

    for(int L = 1; L <= D; L++){
        // Compute new dp for length L
        vector<ll> ndp(MAX_SUM + 1, 0);
        vector<ll> nsum(MAX_SUM + 1, 0);
        for(int s = 0; s <= MAX_SUM; s++){
            if(dp[s] == 0 && sum_val[s] == 0) continue;
            for(int d = 0; d <= 9; d++){
                int ns = s + d * d;
                if(ns > MAX_SUM) continue;
                ndp[ns] = (ndp[ns] + dp[s]) % MOD;
                nsum[ns] = (nsum[ns] + sum_val[s] * 10 + d * dp[s]) % MOD;
            }
        }

        // Now we have dp_old = dp (length L-1 strings) and dp_new = ndp (length L strings)
        // dp_old is the state for length L-1
        // For exact length L numbers:
        for(int first_d = 1; first_d <= 9; first_d++){
            for(int sq : squares){
                int rem = sq - first_d * first_d;
                if(rem < 0 || rem > MAX_SUM) continue;
                ll cnt = dp[rem];
                if(cnt == 0) continue;
                ll contrib = (first_d * pow10[L-1] % MOD * cnt % MOD + sum_val[rem]) % MOD;
                total = (total + contrib) % MOD;
            }
        }

        dp = ndp;
        sum_val = nsum;
    }

    cout << total << "\n";
}
