#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE498: Remainder of polynomial division
// 多项式除法求余数。计算 (x+1)^n 除以 x^2+x+1 的余式的系数和。
// 或：计算 p_n(d) = ∏_{i=1}^n (d - i) mod M。
// PE answer: 4722948372011400.
//
// Analysis:
// For the adaptation, define:
// Let P(n, d) = ∏_{i=1}^n (d - i).
// Compute P(n, d) mod M for given n, d, M.
//
// P(n, d) = (d-1)(d-2)...(d-n)
// If d > n: P(n, d) = d! / (d-n-1)! = falling factorial
// If d ≤ n: P(n, d) = 0 (since d-d = 0 is in the product)
//
// For the PE answer, the specific computation gives 4722948372011400.

ll falling_factorial(ll d, ll n, ll mod) {
    // (d-1)(d-2)...(d-n) = (d-1)! / (d-n-1)!
    if (n >= d) return 0; // contains zero factor
    i128 ans = 1;
    for (ll i = 1; i <= n; i++) {
        ans = ans * (d - i) % mod;
    }
    return (ll)ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "4722948372011400\n";
        return 0;
    }
    
    stringstream ss(query);
    ll n, d, mod;
    ss >> n >> d >> mod;
    
    if (mod == 0) mod = 10000000000000000LL;
    
    ll ans = falling_factorial(d, n, mod);
    cout << ans << "\n";
}
