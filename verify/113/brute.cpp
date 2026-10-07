#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Brute force: enumerate all numbers < 10^D and count non-bouncy
// Only works for small D (≤ 7) due to time

bool is_bouncy(ll x) {
    string s = to_string(x);
    if (s.size() <= 1) return false;
    bool inc = true, dec = true;
    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] < s[i-1]) inc = false;
        if (s[i] > s[i-1]) dec = false;
    }
    return !inc && !dec;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    if (D > 7) {
        cout << "0\n"; // brute too slow, will be verified by std only
        return 0;
    }

    ll limit = 1;
    for (int i = 0; i < D; i++) limit *= 10;

    ll ans = 0;
    for (ll i = 1; i < limit; i++) {
        if (!is_bouncy(i)) ans++;
    }
    cout << ans << "\n";
    return 0;
}
