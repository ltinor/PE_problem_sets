#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Independent naive brute force: actually construct the swapped number
// and test divisibility by 7 directly (no modular-weight shortcut).
bool ok(ll n) {
    if (n % 7 == 0) return false;
    string s = to_string(n);
    int d = (int)s.size();

    for (int i = 0; i < d; i++) {
        for (int j = i + 1; j < d; j++) {
            if (s[i] == s[j]) continue;
            if (i == 0 && s[j] == '0') continue; // leading zero after swap

            string t = s;
            swap(t[i], t[j]);
            ll v = stoll(t);
            if (v % 7 == 0) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll n = 1; n < N; n++) {
        if (ok(n)) ans++;
    }
    cout << ans << "\n";
    return 0;
}
