#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    vector<ll> ans;
    ans.push_back(1);

    for (int r = 1; ; r++) {
        if (r >= 2) {
            ll s = 3LL * r * (r - 1) + 2;
            int cnt = 0;
            if (is_prime(6LL * r - 1)) cnt++;
            if (is_prime(6LL * r + 1)) cnt++;
            if (is_prime(12LL * r + 5)) cnt++;
            if (cnt == 3) ans.push_back(s);
        }

        ll e = 3LL * r * (r + 1) + 1;
        int cnt = 0;
        if (is_prime(6LL * r - 1)) cnt++;
        if (is_prime(6LL * r + 5)) cnt++;
        if (is_prime(12LL * r - 7)) cnt++;
        if (cnt == 3) ans.push_back(e);

        if ((int)ans.size() >= K) {
            sort(ans.begin(), ans.end());
            cout << ans[K - 1] << "\n";
            return 0;
        }
    }

    return 0;
}
