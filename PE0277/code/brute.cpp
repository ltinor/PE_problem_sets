#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Apply one step of modified Collatz
ll step(ll x) {
    if (x % 3 == 0) return x / 3;
    if (x % 3 == 1) return (4 * x + 2) / 3;
    return (2 * x - 1) / 3;
}

char op_char(ll x) {
    if (x % 3 == 0) return 'D';
    if (x % 3 == 1) return 'U';
    return 'd';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    ll T;
    cin >> S >> T;

    for (ll a1 = T + 1; ; a1++) {
        ll cur = a1;
        bool ok = true;
        for (size_t i = 0; i < S.size(); i++) {
            if (cur == 1 && i < S.size()) { ok = false; break; }
            char expected = S[i];
            char actual = op_char(cur);
            if (actual != expected) { ok = false; break; }
            cur = step(cur);
        }
        if (ok) {
            cout << a1 << "\n";
            return 0;
        }
    }
    return 0;
}
