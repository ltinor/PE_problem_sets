#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 236: Luxury Hampers
// Input: 5 lines, each with a_i b_i
// Output: largest m = u/v (reduced fraction) satisfying the paradox

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ll> a(5), b(5);
    for (int i = 0; i < 5; i++) cin >> a[i] >> b[i];

    ll sum_a = 0, sum_b = 0;
    for (int i = 0; i < 5; i++) { sum_a += a[i]; sum_b += b[i]; }

    // Find product with smallest a_i * b_i for enumeration
    int best = 0;
    ll best_sz = a[0] * b[0];
    for (int i = 1; i < 5; i++) {
        if (a[i] * b[i] < best_sz) { best_sz = a[i] * b[i]; best = i; }
    }

    // Generate all m = y * a_best / (x * b_best) as reduced fractions from product 'best'
    // Only consider m > 1 (y * a_best > x * b_best)
    set<pair<ll,ll>> candidates;

    ll A = a[best], B = b[best];
    for (ll x = 1; x <= A; x++) {
        for (ll y = 0; y <= B; y++) {
            ll num = y * A;
            ll den = x * B;
            if (num <= den) continue; // m <= 1
            ll g = std::gcd(num, den);
            candidates.insert({num/g, den/g});
        }
    }

    // For each candidate, check per-product feasibility for all products
    // and overall condition
    vector<pair<ll,ll>> valid;

    for (auto [p, q] : candidates) {
        // Per-product check: need gcd(a_i*q, b_i*p) >= p
        bool ok = true;
        vector<ll> alpha(5), beta(5), maxk(5);
        for (int i = 0; i < 5; i++) {
            ll g = std::gcd(a[i] * q, b[i] * p);
            if (g < p) { ok = false; break; }
            alpha[i] = a[i] * q / g;
            beta[i] = b[i] * p / g;
            maxk[i] = g / p;
        }
        if (!ok) continue;

        // Overall condition: sum(k_i * alpha_i) * q * sum_b = sum(k_i * beta_i) * p * sum_a
        ll L = q * sum_b;
        ll R = p * sum_a;

        // Quick check: k_i = 1 for all
        ll sx = 0, sy = 0;
        for (int i = 0; i < 5; i++) { sx += alpha[i]; sy += beta[i]; }
        if ((__int128)sx * L == (__int128)sy * R) {
            valid.push_back({p, q});
            continue;
        }

        // Meet-in-the-middle for more flexible k_i values
        // Split: products 0,1 vs 2,3,4
        const ll KMAX = 20;
        bool found = false;

        map<ll, ll> diffA; // difference -> min VA? just existence
        ll km0 = min(maxk[0], KMAX);
        ll km1 = min(maxk[1], KMAX);
        for (ll k0 = 1; k0 <= km0; k0++) {
            for (ll k1 = 1; k1 <= km1; k1++) {
                __int128 va = (__int128)k0 * alpha[0] + (__int128)k1 * alpha[1];
                __int128 vb = (__int128)k0 * beta[0] + (__int128)k1 * beta[1];
                __int128 d = va * L - vb * R;
                // d is the "excess" from group A
                // We need d + dB = 0, i.e., dB = -d
                if (d >= -1e18 && d <= 1e18) {
                    diffA[(ll)d] = 1;
                }
            }
        }

        ll km2 = min(maxk[2], KMAX);
        ll km3 = min(maxk[3], KMAX);
        ll km4 = min(maxk[4], KMAX);
        for (ll k2 = 1; k2 <= km2 && !found; k2++) {
            for (ll k3 = 1; k3 <= km3 && !found; k3++) {
                for (ll k4 = 1; k4 <= km4 && !found; k4++) {
                    __int128 va = (__int128)k2 * alpha[2] + (__int128)k3 * alpha[3] + (__int128)k4 * alpha[4];
                    __int128 vb = (__int128)k2 * beta[2] + (__int128)k3 * beta[3] + (__int128)k4 * beta[4];
                    __int128 dB = va * L - vb * R;
                    if (dB >= -1e18 && dB <= 1e18) {
                        if (diffA.count(-(ll)dB)) {
                            found = true;
                        }
                    }
                }
            }
        }

        if (found) {
            valid.push_back({p, q});
        }
    }

    // Output largest m
    sort(valid.begin(), valid.end(), [](auto& x, auto& y) {
        return (__int128)x.first * y.second > (__int128)y.first * x.second;
    });

    if (!valid.empty()) {
        auto [p, q] = valid[0];
        ll g = std::gcd(p, q);
        cout << p/g << "/" << q/g << "\n";
    }

    return 0;
}
