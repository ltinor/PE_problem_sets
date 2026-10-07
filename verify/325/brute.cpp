#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: compute losing positions via game tree DP
// for small N

bool memo[101][101];
bool computed[101][101];

// Returns true if (a,b) is losing (assuming a < b)
bool losing(ll a, ll b) {
    if (a > b) swap(a, b);
    if (a == 0) return false;
    if (b % a == 0) return false; // can take all
    if (computed[a][b]) return memo[a][b];
    computed[a][b] = true;

    if (b < 2*a) {
        // Only move: (b-a, a)
        memo[a][b] = !losing(b - a, a);
        return memo[a][b];
    }

    // b >= 2*a: check all moves
    ll q = b / a;
    for (ll k = 1; k <= q; k++) {
        ll nb = b - k * a;
        if (nb == 0) { memo[a][b] = false; return false; }
        if (losing(min(a, nb), max(a, nb))) {
            memo[a][b] = false; // found winning move
            return false;
        }
    }
    memo[a][b] = true;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    ll N = stoll(s);

    if (N > 100) {
        cout << "-1\n";
        return 0;
    }

    memset(computed, 0, sizeof(computed));
    ll sum_xy = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = a + 1; b <= N; b++) {
            if (losing(a, b)) {
                sum_xy += a + b;
            }
        }
    }
    cout << sum_xy << "\n";
    return 0;
}
