#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll U;
    cin >> U;

    vector<int> pr = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    set<ll> distinct_pf;

    // Generate admissible numbers: DFS on prime index
    // cur = current product (always even once past prime 2)
    // idx = index of prime we're about to add
    function<void(int, ll)> dfs = [&](int idx, ll cur) {
        if (cur >= U) return;
        if (idx >= (int)pr.size()) return;

        ll p = pr[idx];
        // Multiply by p at least once
        ll val = cur;
        if (val > U / p) return;
        val *= p;

        while (val < U) {
            // Now N = val has prime factors {2, 3, ..., pr[idx]}
            // Compute pseudo-Fortunate number
            ll M = 2;
            while (!is_prime(val + M)) M++;
            distinct_pf.insert(M);

            // Try adding the next prime
            dfs(idx + 1, val);

            if (val > U / p) break;
            val *= p;
        }
    };

    // Start with 2^a (powers of 2) - first prime is 2
    dfs(0, 1);

    ll sum = 0;
    for (ll m : distinct_pf) sum += m;
    cout << sum << "\n";

    return 0;
}
