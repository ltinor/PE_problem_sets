#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1000000007LL;

ll f(ll a, ll b) {
    ll ones = 0;
    while (a != 0 || b != 0) {
        if ((a + b) & 1) {
            ones++;
            a -= 1;
        }
        ll na = (-a + b) / 2;
        ll nb = (-a - b) / 2;
        a = na; b = nb;
    }
    return ones;
}

int main() {
    string q; getline(cin, q);
    ll L = stoll(q);
    if (L > 50) { cout << "0\n"; return 0; }
    ll sum = 0;
    for (ll a = -L; a <= L; a++)
        for (ll b = -L; b <= L; b++)
            sum = (sum + f(a, b)) % MOD;
    cout << sum << "\n";
}
