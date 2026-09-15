#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll phi(ll n) {
    ll result = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K, T;
    cin >> K >> T;

    vector<ll> nums;
    for (ll n = 1; nums.size() < (size_t)T && n <= 10000000; n++) {
        if (phi(n) == K) {
            nums.push_back(n);
        }
    }

    if (nums.size() >= (size_t)T) {
        cout << nums[T - 1] << "\n";
    } else {
        cout << "-1\n";
    }

    return 0;
}
