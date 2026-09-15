#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE452 brute: count tuples by direct enumeration
ll F_brute(ll m, ll n) {
    ll cnt = 0;
    // For small m,n only: enumerate all n-tuples
    // Use recursive approach with pruning
    function<void(int, ll)> dfs = [&](int depth, ll prod) {
        if (depth == n) {
            cnt++;
            return;
        }
        for (ll a = 1; a <= m; a++) {
            if (prod * a > m) break;
            dfs(depth + 1, prod * a);
        }
    };
    dfs(0, 1);
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll m, n; cin >> m >> n;
    if (m <= 10 && n <= 10) {
        cout << F_brute(m, n) << "\n";
    } else {
        cout << "-1\n";
    }
}
