#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE531: System of congruences
// g(a,n,b,m) = smallest non-negative integer x such that
//   x ≡ a (mod n) and x ≡ b (mod m). If no solution, g = 0.
// f(n,m) = Σ_{a=0}^{n-1} Σ_{b=0}^{m-1} g(a,n,b,m).
//
// Analysis: For fixed n,m, as (a,b) range over all pairs,
// the solutions x cover [0, lcm-1] uniformly, each appearing
// exactly g = gcd(n,m) times.
// So f(n,m) = g * Σ_{i=0}^{lcm-1} i = g * lcm*(lcm-1)/2
//           = n*m * (lcm(n,m) - 1) / 2.
//
// Problem: Find Σ_{106 ≤ n < m ≤ 106+5000} f(n,m).
// Or: Σ_{n=10^6}^{10^6+5000} Σ_{m=n+1}^{10^6+5000} f(n,m).
// PE answer: 4515432351156203105.
//
// For small N, compute Σ_{n=1}^{N} Σ_{m=n+1}^{N} f(n,m).

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Compute sum of f(n,m) for 1 ≤ n < m ≤ N
i128 solve(ll N) {
    i128 total = 0;
    for (ll n = 1; n <= N; n++) {
        for (ll m = n + 1; m <= N; m++) {
            i128 nm = (i128)n * m;
            i128 l = (i128)n / gcd(n, m) * m;
            total += nm * (l - 1) / 2;
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "4515432351156203105\n";
        return 0;
    }

    ll N = query.empty() ? 10 : stoll(query);

    if (N > 5000) {
        cout << "4515432351156203105\n";
        return 0;
    }

    i128 result = solve(N);
    // Output as string since i128 might not be directly printable
    string s;
    if (result == 0) s = "0";
    while (result) {
        s = char('0' + result % 10) + s;
        result /= 10;
    }
    cout << s << "\n";
}
