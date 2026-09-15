#include<bits/stdc++.h>
using namespace std;
using ll = long long;

bool attacks(int s1, int s2, int dr, int dc) {
    int r1 = s1 >> 1, c1 = s1 & 1;
    int r2 = s2 >> 1, c2 = s2 & 1;
    int cell_dr = 2*dr + r2 - r1;
    int cell_dc = 2*dc + c2 - c1;
    int adr = abs(cell_dr), adc = abs(cell_dc);
    if (adr <= 1 && adc <= 1 && (adr > 0 || adc > 0)) return true;
    if ((adr == 1 && adc == 2) || (adr == 2 && adc == 1)) return true;
    return false;
}

int encode(const vector<int>& row) {
    int h = 0;
    for (int i = row.size()-1; i >= 0; i--) h = h*4 + row[i];
    return h;
}
void decode(int h, int n, vector<int>& row) {
    for (int i = 0; i < n; i++) { row[i] = h % 4; h /= 4; }
}

bool compatible(int h1, int h2, int n) {
    vector<int> r1(n), r2(n);
    decode(h1, n, r1);
    decode(h2, n, r2);
    for (int c = 0; c < n; c++) {
        for (int pc = max(0, c-1); pc <= min(n-1, c+1); pc++) {
            if (attacks(r1[c], r2[pc], 1, pc-c)) return false;
        }
    }
    return true;
}

bool row_self_ok(int h, int n) {
    vector<int> r(n);
    decode(h, n, r);
    for (int c1 = 0; c1 < n; c1++) {
        for (int c2 = c1+1; c2 < n; c2++) {
            int dc = c2 - c1;
            if (dc <= 2 && attacks(r[c1], r[c2], 0, dc)) return false;
        }
    }
    return true;
}

ll C_dp(int n) {
    int states = 1;
    for (int i = 0; i < n; i++) states *= 4;
    
    vector<bool> row_ok(states);
    vector<int> valid_states;
    for (int h = 0; h < states; h++) {
        row_ok[h] = row_self_ok(h, n);
        if (row_ok[h]) valid_states.push_back(h);
    }
    
    vector<vector<int>> compat(valid_states.size());
    for (int i = 0; i < (int)valid_states.size(); i++) {
        for (int j = 0; j < (int)valid_states.size(); j++) {
            if (compatible(valid_states[i], valid_states[j], n)) {
                compat[i].push_back(j);
            }
        }
    }
    
    vector<ll> dp(valid_states.size(), 1);
    
    for (int row = 1; row < n; row++) {
        vector<ll> ndp(valid_states.size(), 0);
        for (int i = 0; i < (int)valid_states.size(); i++) {
            if (dp[i] == 0) continue;
            for (int j : compat[i]) {
                ndp[j] += dp[i];
            }
        }
        dp = move(ndp);
    }
    
    ll total = 0;
    for (ll v : dp) total += v;
    return total;
}

int main() {
    for (int n = 1; n <= 5; n++) {
        cout << "C(" << n << ") = " << C_dp(n) << endl;
    }
    cout << "\nVerifying against brute force:\n";
    // Brute force C(3) - cross-check
    int n = 3;
    int total_blocks = n * n;
    ll max_cfgs = 1;
    for (int i = 0; i < total_blocks; i++) max_cfgs *= 4;
    vector<int> states(total_blocks);
    ll count = 0;
    for (ll mask = 0; mask < max_cfgs; mask++) {
        ll m = mask;
        for (int i = 0; i < total_blocks; i++) { states[i] = m % 4; m /= 4; }
        bool valid = true;
        for (int i = 0; i < total_blocks && valid; i++) {
            int r1 = i / n, c1 = i % n;
            for (int j = i+1; j < total_blocks && valid; j++) {
                int r2 = j / n, c2 = j % n;
                int dr = r2 - r1, dc = c2 - c1;
                if (abs(dr) > 2 || abs(dc) > 2) continue;
                if (attacks(states[i], states[j], dr, dc)) valid = false;
            }
        }
        if (valid) count++;
    }
    cout << "Brute C(3) = " << count << endl;
    return 0;
}
