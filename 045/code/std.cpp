#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll H(ll n) {
    return n * (2LL * n - 1);
}

bool is_pentagonal(ll x) {
    ll disc = 1 + 24 * x;
    ll sq = (ll)sqrt(disc);
    if (sq * sq != disc) return false;
    return (1 + sq) % 6 == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    int cnt = 0;
    ll n = 1;

    while (true) {
        ll h = H(n);
        if (is_pentagonal(h)) {
            cnt++;
            if (cnt == K) {
                cout << h << "\n";
                return 0;
            }
        }
        n++;
    }
}
