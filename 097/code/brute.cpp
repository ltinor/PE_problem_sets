#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 10000000000LL;

ll fast_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (ll)((__int128)res * base % mod);
        base = (ll)((__int128)base * base % mod);
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll A, B, C;
    cin >> A >> B >> C;

    ll pow2b = fast_pow(2, B, MOD);
    ll ans = (ll)(((__int128)A * pow2b + C) % MOD);

    cout << setw(10) << setfill('0') << ans << "\n";
    return 0;
}
