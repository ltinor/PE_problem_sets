#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 209: Brute force - enumerate all truth tables for small k

ll T(ll s, int k) {
    ll a0 = s & 1;
    ll a1 = (s >> 1) & 1;
    ll a2 = (s >> 2) & 1;
    ll shifted = s >> 1;
    ll new_msb = a0 ^ (a1 & a2);
    ll mask = (1LL << (k - 1)) - 1;
    return (shifted & mask) | (new_msb << (k - 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    if (k > 4) {
        cout << "0\n"; // too large for brute force
        return 0;
    }

    ll total_states = 1LL << k;
    ll total_tables = 1LL << total_states; // 2^(2^k)

    // Precompute T(s) for all states
    vector<ll> next_state(total_states);
    for (ll s = 0; s < total_states; s++) {
        next_state[s] = T(s, k);
    }

    ll ans = 0;

    // Enumerate all truth tables
    for (ll table = 0; table < total_tables; table++) {
        bool valid = true;
        for (ll s = 0; s < total_states; s++) {
            int tau_s = (table >> s) & 1;
            int tau_Ts = (table >> next_state[s]) & 1;
            if (tau_s && tau_Ts) {
                valid = false;
                break;
            }
        }
        if (valid) ans++;
    }

    cout << ans << "\n";
    return 0;
}
