#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE423 brute: compute C(n) by DP for small n

const ll MOD = 1000000007;

// C(n): count sequences of length n with c <= pi(n)
ll brute_C(ll n) {
    // f(len, k) = #sequences of length len with exactly k consecutive-equal pairs
    // f(1,0) = 6, f(1,k>0) = 0
    // f(len, k) = 5*f(len-1, k) + f(len-1, k-1)
    vector<vector<ll>> f(2, vector<ll>(n + 1, 0));
    int cur = 0;
    f[cur][0] = 6;
    for (int len = 2; len <= n; len++) {
        int nxt = 1 - cur;
        f[nxt][0] = (5 * f[cur][0]) % MOD;
        for (int k = 1; k < len; k++) {
            f[nxt][k] = (5 * f[cur][k] + f[cur][k-1]) % MOD;
        }
        cur = nxt;
    }

    // Compute pi(n)
    int pi_n = 0;
    vector<bool> isp(n + 1, true);
    isp[0] = isp[1] = false;
    for (int i = 2; i <= n; i++) {
        if (isp[i]) {
            pi_n++;
            for (int j = i * i; j <= n; j += i) isp[j] = false;
        }
    }

    ll ans = 0;
    for (int k = 0; k <= pi_n && k < n; k++) {
        ans = (ans + f[cur][k]) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll L; cin >> L;
    if (L > 100) { cout << "0\n"; return 0; }

    ll ans = 0;
    for (ll n = 1; n <= L; n++) {
        ans = (ans + brute_C(n)) % MOD;
    }
    cout << ans << "\n";
}
