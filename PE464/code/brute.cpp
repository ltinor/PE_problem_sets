#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE464 brute: direct O(n^2) for small n

vector<int> compute_mu(int n) {
    vector<int> mu(n + 1, 1);
    vector<int> primes;
    vector<bool> is_composite(n + 1, false);
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!is_composite[i]) { primes.push_back(i); mu[i] = -1; }
        for (int p : primes) {
            if ((ll)i * p > n) break;
            is_composite[i * p] = true;
            if (i % p == 0) { mu[i * p] = 0; break; }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}

ll C_brute(int n) {
    vector<int> mu = compute_mu(n);
    vector<int> P_plus(n + 1, 0), P_minus(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        P_plus[i] = P_plus[i-1] + (mu[i] == 1);
        P_minus[i] = P_minus[i-1] + (mu[i] == -1);
    }
    ll ans = 0;
    for (int b = 1; b <= n; b++) {
        for (int a = 1; a <= b; a++) {
            ll p = P_plus[b] - P_plus[a-1];
            ll m = P_minus[b] - P_minus[a-1];
            if (99 * m <= 100 * p && 99 * p <= 100 * m) ans++;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    if (n <= 5000) {
        cout << C_brute(n) << "\n";
    } else {
        cout << "-1\n";
    }
}
