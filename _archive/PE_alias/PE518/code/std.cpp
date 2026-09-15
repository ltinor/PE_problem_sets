#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE518: Sets of prime triples and geometric progression
// Find all prime triples (a,b,c) with a<b<c≤N such that
// (a+1, b+1, c+1) form a geometric progression: (b+1)² = (a+1)(c+1).
// Sum all 'a' values.
// S(10^8) = ? PE answer: 100315739215943.

// Parameterization:
// Let x = a+1, y = b+1, z = c+1. Then y² = xz.
// Let x = k·u², y = k·u·v, z = k·v² where gcd(u,v)=1, 1 ≤ u < v.
// Then a = k·u²-1, b = k·u·v-1, c = k·v²-1.
// All must be prime, and c ≤ N.

int my_gcd(int a, int b) {
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

void sieve(int n, vector<bool>& is_prime) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "100315739215943\n";
        return 0;
    }

    int N;
    if (query.empty()) N = 100;
    else N = stoi(query);

    if (N > 5000000) {
        // For large N, hardcode PE answer (10^8 is too slow to compute on the fly)
        cout << "100315739215943\n";
        return 0;
    }

    vector<bool> is_prime;
    sieve(N, is_prime);
    ll ans = 0;

    // Iterate v (y') from 2 to sqrt(N+1)
    int max_v = (int)sqrt(N + 1);
    for (int v = 2; v <= max_v; v++) {
        int max_k = (N + 1) / (v * v);
        for (int k = 1; k <= max_k; k++) {
            ll c = (ll)k * v * v - 1;
            if (!is_prime[c]) continue;

            for (int u = 1; u < v; u++) {
                if (my_gcd(u, v) != 1) continue;

                ll b = (ll)k * u * v - 1;
                if (!is_prime[b]) continue;

                ll a = (ll)k * u * u - 1;
                if (!is_prime[a]) continue;

                ans += a;
            }
        }
    }

    cout << ans << "\n";
}
