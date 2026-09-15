#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE474 brute: enumerate divisors for very small n!

int main() {
    ll N, D; cin >> N >> D;
    if (N > 8) { cout << "0\n"; return 0; }
    ll fact = 1;
    for (ll i = 2; i <= N; i++) fact *= i;

    ll mod = 1, tmp = D;
    while (tmp) { mod *= 10; tmp /= 10; }
    if (mod == 0) mod = 10;

    ll cnt = 0;
    for (ll d = 1; d * d <= fact; d++) {
        if (fact % d == 0) {
            if (d % mod == D % mod) cnt++;
            ll o = fact / d;
            if (o != d && o % mod == D % mod) cnt++;
        }
    }
    cout << cnt << "\n";
}
