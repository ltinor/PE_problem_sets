#include<bits/stdc++.h>
using namespace std;
using ll=long long;

// PE407 brute: compute M(n) by checking all a < n
ll M_brute(ll n) {
    ll best = 0;
    for (ll a = 1; a < n; a++) {
        if ((a * (a - 1)) % n == 0) {
            if (a > best) best = a;
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    ll total = 0;
    for (ll n = 1; n <= N; n++) total += M_brute(n);
    cout << total << "\n";
}
