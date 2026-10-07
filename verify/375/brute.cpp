#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N;
    cin >> N;

    const ll MOD = 50515093;
    vector<ll> S(N + 1);
    S[0] = 290797;
    for (ll i = 1; i <= N; i++)
        S[i] = (S[i-1] * S[i-1]) % MOD;

    unsigned long long ans = 0;
    for (ll i = 1; i <= N; i++) {
        ll mn = S[i];
        for (ll j = i; j <= N; j++) {
            mn = min(mn, S[j]);
            ans += mn;
        }
    }
    cout << ans << "\n";
    return 0;
}
