#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: same algorithm, independently implemented

ll phi_val;

ll my_gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

bool coprime(ll e) {
    return my_gcd(e, phi_val) == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll p, q;
    cin >> p >> q;

    phi_val = (p - 1) * (q - 1);

    ll min_U = p * q + 1;
    vector<ll> best_e;

    for (ll e = 2; e < phi_val; e++) {
        if (!coprime(e)) continue;

        ll g1 = my_gcd(e - 1, p - 1);
        ll g2 = my_gcd(e - 1, q - 1);
        ll U = (1 + g1) * (1 + g2);

        if (U < min_U) {
            min_U = U;
            best_e.clear();
            best_e.push_back(e);
        } else if (U == min_U) {
            best_e.push_back(e);
        }
    }

    ll sum = 0;
    for (ll e : best_e) sum += e;
    cout << sum << "\n";

    return 0;
}
