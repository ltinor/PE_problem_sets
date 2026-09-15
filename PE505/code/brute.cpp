#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force A(n) computation with full precision for verification
unordered_map<ll, ll> memo;

ll A_brute(ll n) {
    if (n == 0) return 1;
    if (n == 1) return 3;
    if (n < 0) return 0;
    if (memo.count(n)) return memo[n];
    ll res;
    if (n % 2 == 0) {
        ll m = n / 2;
        res = A_brute(m) + A_brute(m - 1) + m;
    } else {
        ll m = n / 2;
        res = 2 * A_brute(m) + A_brute(m - 1) + m;
    }
    return memo[n] = res;
}

int main() {
    string query;
    getline(cin, query);
    ll N = stoll(query);
    if (N > 1000) { cout << "0\n"; return 0; }

    // Output A(N) (full precision, no mod)
    cout << A_brute(N) << "\n";
}
