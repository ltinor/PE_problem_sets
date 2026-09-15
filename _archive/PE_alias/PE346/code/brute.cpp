#include<bits/stdc++.h>
using namespace std;
#define ll long long
using i128 = __int128;

// PE346 brute: same logic as std, enumerate all repunits and deduplicate
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll LIM;
    cin >> LIM;

    unordered_map<ll, int> cnt; // count representations per value

    // n=1: value=1, repunit in every base
    cnt[1] = 2; // at least 2 bases

    // Enumerate repunits: base b≥2, length n≥2
    for (ll b = 2; ; b++) {
        i128 val = b + 1; // n=2
        if (val > LIM) break;
        if (val <= LIM) cnt[(ll)val]++;

        i128 p = (i128)b * b;
        for (ll n = 3; ; n++) {
            p *= b;
            val = (p - 1) / (b - 1);
            if (val > LIM) break;
            cnt[(ll)val]++;
        }
    }

    ll ans = 0;
    for (auto &kv : cnt) {
        if (kv.second >= 2) ans += kv.first;
    }
    cout << ans << "\n";
    return 0;
}
