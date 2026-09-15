#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll g_val(ll v) {
    if (v <= 0) return 0;
    string s = to_string(v);
    int d = s.size();
    ll ans = 0;
    for (int k = 1; k <= d; k++) {
        bool is_border = true;
        for (int i = 0; i < k; i++) {
            if (s[i] != s[d - k + i]) {
                is_border = false;
                break;
            }
        }
        if (is_border) {
            ll pw = 1;
            for (int j = 0; j < k; j++) pw *= 10;
            ans += pw;
        }
    }
    ans -= (d - 1);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D, K;
    cin >> D >> K;

    ll N = 1;
    for (int i = 0; i < D; i++) N *= 10;

    ll U = 1;
    for (int i = 0; i < K; i++) U *= 10;
    U--;

    ll ans = 0;
    for (ll n = 2; n <= U; n++) {
        ll v = N / n;
        ans += g_val(v);
    }

    cout << ans << "\n";
    return 0;
}
