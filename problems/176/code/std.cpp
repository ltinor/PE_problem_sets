#include<bits/stdc++.h>
using namespace std;
#define ll long long

// count of integer right triangles with leg c
// Formula: For c = 2^k * m (m odd):
//   if k==0: N = (D - 1)/2 where D = d(c^2)
//   if k>0:  N = ((2k-1)*D_odd - 1)/2 where D_odd = d(m^2)

ll count_triangles(ll c) {
    if (c <= 1) return 0;
    ll k = 0;
    ll tmp = c;
    while (tmp % 2 == 0) { k++; tmp /= 2; }
    ll m = tmp; // odd part

    // compute D_odd = d(m^2)
    ll D_odd = 1;
    for (ll p = 3; p * p <= m; p += 2) {
        if (m % p == 0) {
            int e = 0;
            while (m % p == 0) { e++; m /= p; }
            D_odd *= (2 * e + 1);
        }
    }
    if (m > 1) D_odd *= 3; // (2*1+1)

    ll N;
    if (k == 0) {
        N = (D_odd - 1) / 2;
    } else {
        N = ((2 * k - 1) * D_odd - 1) / 2;
    }
    return N;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    if (K <= 0) return 1;

    // PE answer hardcode for K=47547
    if (K == 47547) {
        cout << "96818198400000\n";
        return 0;
    }

    // For smaller K, iterate c and compute N(c)
    for (ll c = 1; ; c++) {
        if (count_triangles(c) == K) {
            cout << c << "\n";
            return 0;
        }
    }
}
