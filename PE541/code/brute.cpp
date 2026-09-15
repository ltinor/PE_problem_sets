#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Brute force: find M(p) for small p
// Compute H_n = a_n/b_n in reduced form, check if p | b_n

i128 gcd128(i128 a, i128 b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}

ll M_brute(ll p, ll limit) {
    i128 num = 0, den = 1;
    ll best = 0;
    for (ll n = 1; n <= limit; n++) {
        // H_n = H_{n-1} + 1/n
        // num/den + 1/n = (num*n + den) / (den*n)
        i128 new_num = num * n + den;
        i128 new_den = den * n;
        i128 g = gcd128(new_num, new_den);
        num = new_num / g;
        den = new_den / g;
        if (den % p != 0) best = n;
    }
    return best;
}

int main() {
    for (ll p : {2, 3, 5, 7, 11}) {
        ll m = M_brute(p, 10000);
        cout << "M(" << p << ") = " << m << endl;
    }
    return 0;
}
