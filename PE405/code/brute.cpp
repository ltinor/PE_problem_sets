#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// PE405 brute: compute f(n) via recurrence
// f(0)=f(1)=0, f(n)=4*f(n-1)+2^(n-1)-1 for n>=2
// Closed: f(n) = (4^n - 3*2^n + 2)/6

using ull = unsigned long long;

ull f(ll n) {
    if (n <= 1) return 0;
    ull p4 = 1, p2 = 1;
    for (ll i = 0; i < n; i++) p4 *= 4;
    for (ll i = 0; i < n; i++) p2 *= 2;
    return (p4 - 3 * p2 + 2) / 6;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;
    if (n <= 60) cout << f(n) << "\n";
    else cout << "0\n";
}
