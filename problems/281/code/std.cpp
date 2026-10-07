#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 281: Sum of f(m,n) ≤ T
// f(m,n) = (1/(mn)) * sum_{d: m|d|mn} φ(mn/d) * (d)! / ((d/m)!^m)
// Using __int128 for intermediate

using i128 = __int128;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

vector<ll> get_divisors(ll n) {
    vector<ll> divs;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divs.push_back(d);
            if (d * d != n) divs.push_back(n / d);
        }
    }
    return divs;
}

// Compute d! / ((d/m)!^m) using gradual multiplication
i128 multinomial(ll d, ll m) {
    ll block = d / m;
    i128 res = 1;
    // Compute the multinomial: d! / (block!^m)
    // Use combinatorial formula: product over blocks
    vector<ll> num, den;
    for (ll i = 2; i <= d; i++) num.push_back(i);
    for (int j = 0; j < m; j++)
        for (ll i = 2; i <= block; i++) den.push_back(i);
    
    // Cancel gcd
    for (size_t i = 0; i < den.size(); i++) {
        for (size_t j = 0; j < num.size() && den[i] > 1; j++) {
            ll g = gcd(num[j], den[i]);
            if (g > 1) { num[j] /= g; den[i] /= g; }
        }
    }
    for (ll x : num) res *= x;
    for (ll x : den) { if (x > 1) res /= x; }
    return res;
}

i128 f(ll m, ll n) {
    ll mn = m * n;
    auto divs = get_divisors(mn);
    i128 total = 0;
    for (ll d : divs) {
        if (d % m != 0) continue;
        i128 term = (i128)phi(mn / d) * multinomial(d, m);
        total += term;
    }
    return total / mn;
}

string to_string_i128(i128 x) {
    if (x == 0) return "0";
    string s;
    while (x > 0) { s += (char)('0'+(int)(x%10)); x /= 10; }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll T;
    cin >> T;
    
    i128 ans = 0;
    i128 limit = (i128)T;
    
    for (ll m = 2; ; m++) {
        i128 f_m1 = f(m, 1);
        if (f_m1 > limit) break;
        for (ll n = 1; ; n++) {
            i128 val = f(m, n);
            if (val > limit) break;
            ans += val;
        }
    }
    
    cout << to_string_i128(ans) << "\n";
}
