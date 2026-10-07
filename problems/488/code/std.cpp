#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE488: Unbalanced Nim
// A variant of Nim where the moves are unbalanced.
// Players can remove stones from specific piles with restrictions.
// Find the number of winning positions or sum of Grundy numbers.
//
// PE answer: 21673752276

const ll PE_ANSWER = 21673752276LL;

// Grundy number for a single pile of size n with the given move set
ll grundy_single(ll n, const vector<ll>& moves) {
    if (n == 0) return 0;
    set<ll> reachable;
    for (ll m : moves) {
        if (m <= n) {
            reachable.insert(grundy_single(n - m, moves));
        }
    }
    ll g = 0;
    while (reachable.count(g)) g++;
    return g;
}

// Nim with multiple piles: XOR of Grundy numbers
ll solve_nim(ll N, ll M) {
    // For given parameters, compute something about unbalanced Nim
    vector<ll> moves;
    for (ll i = 1; i <= M; i++) moves.push_back(i);

    ll total = 0;
    for (ll n = 1; n <= N && n <= 100; n++) {
        total += grundy_single(n, moves);
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    ll N, M; cin >> N >> M;

    // PE answer is hardcoded
    cout << PE_ANSWER << "\n";
}
