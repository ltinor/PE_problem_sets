#include<bits/stdc++.h>
using namespace std;
#define ll long long

int z(ll n) {
    // simple Zeckendorf using greedy
    vector<ll> fib = {1, 2};
    while (fib.back() <= n) fib.push_back(fib.back() + fib[fib.size()-2]);
    int cnt = 0;
    for (int i = fib.size()-1; i >= 0 && n > 0; i--) {
        if (fib[i] <= n) {
            n -= fib[i];
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll i = 1; i < N; i++) {
        ans += z(i);
    }

    cout << ans << "\n";
    return 0;
}
