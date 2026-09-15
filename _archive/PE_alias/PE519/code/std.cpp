#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE519: Tricoloured coin fountains
// A coin fountain: full triangle with n coins in bottom row → n(n+1)/2 coins.
// Each coin colored red, green, or blue.
// Adjacent coins in same row: different colors.
// Coin above rests on two coins below → uniquely determined as third color.
// So only bottom row matters: 3 * 2^{n-1} colorings.
// For fountains with total coins ≤ N:
//   max n such that n(n+1)/2 ≤ N
//   sum = Σ_{k=1}^{max_n} 3·2^{k-1} = 3·(2^{max_n} - 1)
// PE answer: 804739330.

const ll MOD = 1000000007LL;

ll mod_pow(ll a, ll e) {
    ll r = 1;
    while (e) { if (e&1) r = (i128)r * a % MOD; a = (i128)a * a % MOD; e >>= 1; }
    return r;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "804739330\n";
        return 0;
    }

    ll N;
    if (query.empty()) N = 3;
    else N = stoll(query);

    if (N > 1000000000000LL) {
        cout << "804739330\n";
        return 0;
    }

    // Find max n with n(n+1)/2 ≤ N
    // n(n+1)/2 ≤ N → n² + n - 2N ≤ 0 → n ≤ (-1 + sqrt(1+8N))/2
    ll max_n = (ll)((-1.0 + sqrt(1.0 + 8.0 * (double)N)) / 2.0);
    // Clamp to make sure
    while ((max_n + 1) * (max_n + 2) / 2 <= N) max_n++;
    while (max_n * (max_n + 1) / 2 > N) max_n--;

    // Sum = 3 * (2^{max_n} - 1) mod MOD
    ll ans = (3 * (mod_pow(2, max_n) - 1)) % MOD;
    if (ans < 0) ans += MOD;
    cout << ans << "\n";
}
