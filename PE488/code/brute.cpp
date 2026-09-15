#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force Nim Grundy
ll grundy_single(ll n, const vector<ll>& moves) {
    if (n == 0) return 0;
    set<ll> reachable;
    for (ll m : moves) {
        if (m <= n) reachable.insert(grundy_single(n - m, moves));
    }
    ll g = 0;
    while (reachable.count(g)) g++;
    return g;
}

int main() {
    ll N, M; cin >> N >> M;
    vector<ll> moves;
    for (ll i = 1; i <= M; i++) moves.push_back(i);

    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        total += grundy_single(n, moves);
    }
    cout << total << "\n";
}
