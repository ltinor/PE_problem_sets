#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007LL;

ll solve(ll N) {
    if (N == 0) return 0;
    vector<int> bits;
    ll tmp = N;
    while (tmp > 0) { bits.push_back(tmp & 1); tmp >>= 1; }
    reverse(bits.begin(), bits.end());
    int L = bits.size();
    
    cout << "N = " << N << "\n";
    cout << "Binary: ";
    for (int b : bits) cout << b;
    cout << " (" << L << " bits)\n";
    
    vector<ll> pow2(L + 1), pow4(L + 1);
    pow2[0] = 1; pow4[0] = 1;
    for (int i = 1; i <= L; i++) {
        pow2[i] = pow2[i-1] * 2 % MOD;
        pow4[i] = pow4[i-1] * 4 % MOD;
    }
    
    int max_pop = L;
    int states = (L + 1) * 2 * (max_pop + 1);
    vector<ll> dp_cnt(states, 0), dp_sum(states, 0), dp_sum2(states, 0);
    auto idx = [L, max_pop](int pos, int tight, int pop) {
        return (pos * 2 + tight) * (max_pop + 1) + pop;
    };
    
    dp_cnt[idx(0, 1, 0)] = 1;
    
    for (int pos = 0; pos < L; pos++) {
        int bit_pos = L - 1 - pos;
        ll p2 = pow2[bit_pos], p4 = pow4[bit_pos];
        int limit = bits[pos];
        
        for (int tight = 0; tight <= 1; tight++) {
            int max_digit = tight ? limit : 1;
            for (int pop = 0; pop <= pos; pop++) {
                ll cnt = dp_cnt[idx(pos, tight, pop)];
                ll sum = dp_sum[idx(pos, tight, pop)];
                ll sum2 = dp_sum2[idx(pos, tight, pop)];
                if (cnt == 0 && sum == 0 && sum2 == 0) continue;
                
                for (int d = 0; d <= max_digit; d++) {
                    int ntight = tight && (d == limit);
                    int npop = pop + d;
                    ll ncnt = cnt;
                    ll nsum = (sum + d * p2 % MOD * cnt) % MOD;
                    ll nsum2 = (sum2 + 2LL * d * p2 % MOD * sum % MOD + (ll)d * p4 % MOD * cnt) % MOD;
                    nsum2 = (nsum2 + MOD) % MOD;
                    
                    int nidx = idx(pos + 1, ntight, npop);
                    dp_cnt[nidx] = (dp_cnt[nidx] + ncnt) % MOD;
                    dp_sum[nidx] = (dp_sum[nidx] + nsum) % MOD;
                    dp_sum2[nidx] = (dp_sum2[nidx] + nsum2) % MOD;
                }
            }
        }
    }
    
    ll ans = 0;
    for (int tight = 0; tight <= 1; tight++) {
        for (int pop = 0; pop <= max_pop; pop++) {
            int nidx = idx(L, tight, pop);
            ll sum2 = dp_sum2[nidx];
            if (sum2 > 0) {
                ans = (ans + (ll)pop * pop % MOD * sum2) % MOD;
            }
        }
    }
    return ans;
}

int main() {
    // Check powers of 10
    cout << "=== Checking powers of 10 ===\n";
    vector<ll> powers;
    ll p = 1;
    for (int i = 0; i <= 16; i++) {
        powers.push_back(p);
        p *= 10;
    }
    for (ll N : powers) {
        ll ans = solve(N);
        cout << "S(10^" << (int)log10(N) << ") mod MOD = " << ans << "\n\n";
    }
    return 0;
}
