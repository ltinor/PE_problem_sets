#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 1000000000LL;

// Brute force: generate all valid sequences for small n
// using the constraints

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    if (n > 10) {
        // Too large for brute force
        cout << "0\n";
        return 0;
    }

    vector<ll> seq(n+1);
    seq[1] = 2;
    ll cnt = 0;

    function<void(int)> dfs = [&](int i) {
        if (i > n) {
            cnt = (cnt + 1) % MOD;
            return;
        }

        // Determine bounds for x_i
        ll L = seq[i-1] + 1; // strictly increasing
        ll R = (ll)powl(3.0L, i) - 1; // from x_1 constraint

        for (int j = 1; j < i; j++) {
            // (x_i)^j < (x_j+1)^i
            ll ub = (ll)floorl(powl((long double)(seq[j]+1), (long double)i / j) - 1e-12L);
            R = min(R, ub);

            // (x_j)^i < (x_i+1)^j
            ll lb = (ll)floorl(powl((long double)seq[j], (long double)i / j));
            L = max(L, lb);
        }

        for (ll x = L; x <= R; x++) {
            seq[i] = x;
            dfs(i+1);
        }
    };

    dfs(2);
    cout << cnt << "\n";
    return 0;
}
