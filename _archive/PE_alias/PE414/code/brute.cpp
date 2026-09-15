#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE414 brute: Kaprekar constant, same logic for small bases

ll kaprekar_step(ll x, ll b) {
    int digs[5];
    ll tmp = x;
    for (int i = 4; i >= 0; i--) { digs[i] = tmp % b; tmp /= b; }
    sort(digs, digs + 5);
    ll asc = 0, desc = 0;
    for (int i = 0; i < 5; i++) {
        asc = asc * b + digs[i];
        desc = desc * b + digs[4-i];
    }
    return desc - asc;
}

ll find_constant(ll b) {
    ll start = b/2;
    set<ll> seen;
    ll cur = start;
    while (true) {
        if (seen.count(cur)) return cur;
        seen.insert(cur);
        ll nxt = kaprekar_step(cur, b);
        if (nxt == 0) return 0;
        cur = nxt;
    }
}

ll S_brute(ll b) {
    ll b5 = 1;
    for (int i = 0; i < 5; i++) b5 *= b;

    ll C = find_constant(b);
    ll ans = 0;
    for (ll i = 1; i < b5; i++) {
        vector<int> digs(5);
        ll tmp = i;
        for (int j = 4; j >= 0; j--) { digs[j] = tmp % b; tmp /= b; }
        bool all_same = true;
        for (int j = 1; j < 5; j++) if (digs[j] != digs[0]) all_same = false;
        if (i == C || all_same) continue;

        ll cur = i, steps = 0;
        while (cur != C) { cur = kaprekar_step(cur, b); steps++; }
        ans += steps;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll b; cin >> b;
    cout << S_brute(b) << "\n";
}
