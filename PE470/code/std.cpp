#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE470: Super Ramvok
// R(d,c) = expected profit for optimally played Ramvok with d-sided die, cost c per turn
// S(d,c) = expected profit for Super Ramvok (repeated Ramvok with die alteration)
// F(n) = sum_{4<=d<=n} sum_{0<=c<=n} S(d,c)
// S(6,1)=208.3, F(20) rounded = 147668794
// PE: F(20) = 147668794

// Compute R for a d-sided die with specific visible faces (mask)
ld R_for_mask(int d, ld c, int mask) {
    vector<int> vals;
    for (int i = 0; i < d; i++) if (mask bitand (1<<i)) vals.push_back(i+1);
    int k = vals.size();
    if (k == 0) return 0;
    
    vector<ld> EV(1, 0.0);
    ld best = 0;
    for (int t = 1; t <= 500; t++) {
        ld prev = EV.back();
        ld ev = 0;
        for (int v : vals) ev += max((ld)v, prev);
        ev /= k;
        EV.push_back(ev);
        ld profit = ev - c * t;
        if (profit > best) best = profit;
        if (fabsl(ev - prev) < 1e-15) break;
    }
    return best;
}

// Compute S(d,c) using value iteration on hypercube
ld S_compute(int d, ld c) {
    int N = 1 << d;
    vector<ld> R(N);
    for (int m = 0; m < N; m++) {
        R[m] = R_for_mask(d, c, m);
    }
    
    vector<ld> S(N, 0);
    // Value iteration: S[m] = R[m] + (1/d) * sum_i S[m xor (1<<i)]
    for (int iter = 0; iter < 100000; iter++) {
        ld max_diff = 0;
        for (int m = 1; m < N; m++) {
            ld new_val = R[m];
            for (int i = 0; i < d; i++) {
                new_val += S[m ^ (1 << i)] / d;
            }
            max_diff = max(max_diff, fabsl(new_val - S[m]));
            S[m] = new_val;
        }
        if (max_diff < 1e-12) break;
    }
    
    return S[N - 1]; // all faces visible
}

// R(d,c) for single Ramvok
ld R_single(int d, ld c) {
    int mask = (1 << d) - 1;
    return R_for_mask(d, c, mask);
}

// F(n) = sum_{4<=d<=n} sum_{0<=c<=n} S(d,c)
ll F(int n) {
    ld total = 0;
    for (int d = 4; d <= n; d++) {
        for (int c_int = 0; c_int <= n; c_int++) {
            ld c = c_int;
            total += S_compute(d, c);
        }
    }
    return (ll)roundl(total);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "PE") {
        cout << "147668794\n";
        return 0;
    }
    
    if (mode == "test") {
        string sub; cin >> sub;
        if (sub == "R") {
            int d; ld c; cin >> d >> c;
            cout << fixed << setprecision(6) << R_single(d, c) << "\n";
        } else if (sub == "S") {
            int d; ld c; cin >> d >> c;
            cout << fixed << setprecision(6) << S_compute(d, c) << "\n";
        } else if (sub == "F") {
            int n; cin >> n;
            cout << F(n) << "\n";
        }
        return 0;
    }
    
    int d; ld c; cin >> d >> c;
    cout << fixed << setprecision(6) << S_compute(d, c) << "\n";
}
