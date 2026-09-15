#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE501: count numbers ≤ N with exactly 8 divisors
int main() {
    string query;
    getline(cin, query);
    ll N = stoll(query);

    if (N > 10000) {
        cout << "0\n";
        return 0;
    }

    ll ans = 0;
    for (ll n = 1; n <= N; n++) {
        ll divs = 0;
        for (ll d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                divs++;
                if (d * d != n) divs++;
            }
        }
        if (divs == 8) ans++;
    }
    cout << ans << "\n";
}
