#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = a; a + b <= N; b++) {
            for (ll c = b; a + b + c <= N; c++) {
                if (a + b > c && gcd(gcd(a, b), c) == 1)
                    ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
