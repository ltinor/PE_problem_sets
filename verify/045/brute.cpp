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

    // Independent implementation: iterate triangular numbers instead
    ll T_n = 0;
    int cnt = 0;
    for (ll i = 1; ; i++) {
        T_n = i * (i + 1) / 2;
        if (is_pentagonal(T_n)) {
            cnt++;
            if (cnt == K) {
                cout << T_n << "\n";
                return 0;
            }
        }
    }
}
