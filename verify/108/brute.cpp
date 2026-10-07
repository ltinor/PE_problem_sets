#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: same approach but simpler factoring
// Count solutions of 1/x + 1/y = 1/n using divisor count

ll count_solutions(ll n) {
    // Factor n^2 by factoring n and doubling exponents
    ll d = 1;
    ll m = n;
    for (ll p = 2; p * p <= m; p++) {
        if (m % p == 0) {
            int e = 0;
            while (m % p == 0) {
                m /= p;
                e++;
            }
            d *= (2 * e + 1);
        }
    }
    if (m > 1) d *= 3; // (2*1 + 1)
    return (d + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    for (ll n = 1; ; n++) {
        if (count_solutions(n) > K) {
            cout << n << "\n";
            break;
        }
    }

    return 0;
}
