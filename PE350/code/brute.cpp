#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE350 brute: enumerate all sequences for small N and small L
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a,b) * b; }

int main() {
    ll G, L, N, MOD;
    cin >> G >> L >> N >> MOD;

    if (N > 5 || L > 50) {
        // brute only works for very small parameters
        cout << "0\n";
        return 0;
    }

    ll ans = 0;
    vector<ll> seq(N);
    function<void(int)> dfs = [&](int pos) {
        if (pos == N) {
            ll g = seq[0], l = seq[0];
            for (ll x : seq) {
                g = gcd(g, x);
                l = lcm(l, x);
            }
            if (g >= G && l <= L) ans++;
            return;
        }
        for (ll a = 1; a <= L; a++) {
            seq[pos] = a;
            dfs(pos + 1);
        }
    };
    dfs(0);

    cout << ans % MOD << "\n";
    return 0;
}
