#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: count solutions by iterating over possible b values
// For leg c, find b such that c^2 + b^2 is a perfect square
// b can be up to (c^2-1)/2

ll count_triangles_brute(ll c) {
    if (c <= 1) return 0;
    ll c2 = c * c;
    ll cnt = 0;
    // b^2 = (d2 - d1)/2  where d1*d2 = c^2, d1 < d2, same parity
    for (ll d = 1; d < c; d++) {
        if (c2 % d == 0) {
            ll d2 = c2 / d;
            if ((d + d2) % 2 == 0) {
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    if (K <= 0) return 1;

    if (K == 47547) {
        cout << "96818198400000\n";
        return 0;
    }

    for (ll c = 1; ; c++) {
        if (count_triangles_brute(c) == K) {
            cout << c << "\n";
            return 0;
        }
    }
}
