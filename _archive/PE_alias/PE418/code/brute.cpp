#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE418 brute: exhaustive search of factorisation triples

ll f_brute(ll n) {
    vector<ll> divs;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divs.push_back(d);
            if (d * d != n) divs.push_back(n / d);
        }
    }
    sort(divs.begin(), divs.end());

    ll best_sum = LLONG_MAX;
    double best_ratio = 1e30;
    int sz = divs.size();
    for (int i = 0; i < sz; i++) {
        ll a = divs[i];
        for (int j = i; j < sz; j++) {
            ll b = divs[j];
            if (n % (a * b) != 0) continue;
            ll c = n / (a * b);
            if (c < b) continue;
            double ratio = (double)c / a;
            if (ratio < best_ratio - 1e-12) {
                best_ratio = ratio;
                best_sum = a + b + c;
            }
        }
    }
    return best_sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;
    cout << f_brute(n) << "\n";
}
