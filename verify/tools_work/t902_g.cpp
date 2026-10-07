// print G(i,j) = sum_{k=1..ord} [pi^k(j) < pi^k(i)] for all i<j
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char** argv) {
    ll m = atoi(argv[1]);
    ll n = m * (m + 1) / 2;
    vector<ll> sig(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll k = (ll)((sqrtl(8.0L * i + 1) - 1) / 2);
        if (k * (k + 1) / 2 == i) sig[i] = k * (k - 1) / 2 + 1; else sig[i] = i + 1;
    }
    vector<ll> tau(n + 1), tinv(n + 1);
    for (ll i = 1; i <= n; i++) { tau[i] = (1000000007LL % n) * (i % n) % n + 1; tinv[tau[i]] = i; }
    vector<ll> pi(n + 1);
    for (ll i = 1; i <= n; i++) pi[i] = tinv[sig[tau[i]]];
    vector<int> cid(n + 1, -1), off(n + 1, -1);
    vector<vector<int>> cyc;
    for (ll s = 1; s <= n; s++) {
        if (cid[s] != -1) continue;
        int id = cyc.size(); vector<int> c; ll x = s;
        while (cid[x] == -1) { cid[x] = id; off[x] = c.size(); c.push_back(x); x = pi[x]; }
        cyc.push_back(c);
    }
    ll ord = 1;
    for (auto& c : cyc) ord = ord / __gcd(ord, (ll)c.size()) * (ll)c.size();
    vector<vector<ll>> cur(ord + 1, vector<ll>(n + 1));
    for (ll i = 1; i <= n; i++) cur[0][i] = i;
    for (ll k = 1; k <= ord; k++) for (ll i = 1; i <= n; i++) cur[k][i] = pi[cur[k-1][i]];
    printf("G[i][j] (i<j):\n");
    for (ll i = 1; i <= n; i++) for (ll j = i + 1; j <= n; j++) {
        ll g = 0;
        for (ll k = 1; k <= ord; k++) if (cur[k][j] < cur[k][i]) g++;
        if (g) printf("G(%lld,%lld)=%lld  [cyc %d/%d off %d/%d]\n", i, j, g, cid[i], cid[j], off[i], off[j]);
    }
    return 0;
}
