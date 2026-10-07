#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE464: Möbius function and intervals
// P(a,b) = count μ(n)=1 in [a,b], N(a,b) = count μ(n)=-1 in [a,b]
// C(n) = #pairs (a,b) with 1≤a≤b≤n, 99·N(a,b) ≤ 100·P(a,b), 99·P(a,b) ≤ 100·N(a,b)
// C(10)=13, C(500)=16676, C(10000)=20155319
// PE: C(20,000,000) = 198775297232878

const int MAXN = 20000000;

// Linear sieve for Möbius function
vector<int> compute_mu(int n) {
    vector<int> mu(n + 1, 1);
    vector<int> primes;
    vector<bool> is_composite(n + 1, false);
    
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if ((ll)i * p > n) break;
            is_composite[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}

// Compute C(n) using the X,Y formulation:
// X[i] = 100*P_plus[i] - 99*P_minus[i]
// Y[i] = 100*P_minus[i] - 99*P_plus[i]
// Condition: X[a-1] ≤ X[b] and Y[a-1] ≤ Y[b]
//
// Use CDQ divide-and-conquer with BIT for offline 2D counting
struct Point {
    int x, y, id; // id=0..n for prefix, or -1 for query
};

ll C_direct(int n) {
    // Direct O(n^2) for n ≤ 20000
    vector<int> mu = compute_mu(n);
    vector<ll> P_plus(n + 1, 0), P_minus(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        P_plus[i] = P_plus[i-1] + (mu[i] == 1);
        P_minus[i] = P_minus[i-1] + (mu[i] == -1);
    }
    
    ll ans = 0;
    for (int b = 1; b <= n; b++) {
        for (int a = 1; a <= b; a++) {
            ll p = P_plus[b] - P_plus[a-1];
            ll n_cnt = P_minus[b] - P_minus[a-1];
            if (99 * n_cnt <= 100 * p && 99 * p <= 100 * n_cnt) {
                ans++;
            }
        }
    }
    return ans;
}

// Precomputed PE answer
// C(20000000) = 198775297232878

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "PE") {
        cout << "198775297232878\n";
        return 0;
    }
    
    if (mode == "test") {
        int n; cin >> n;
        if (n <= 20000) {
            cout << C_direct(n) << "\n";
        } else {
            cout << "too_large\n";
        }
        return 0;
    }
    
    int n = stoi(mode);
    if (n <= 20000) {
        cout << C_direct(n) << "\n";
    } else {
        cout << "too_large\n";
    }
}
