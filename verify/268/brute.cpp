#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Primes < 100
    vector<int> primes;
    for (int i = 2; i < 100; i++) {
        bool is_prime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) { is_prime = false; break; }
        }
        if (is_prime) primes.push_back(i);
    }

    ll ans = 0;
    for (ll n = 1; n <= N; n++) {
        int cnt = 0;
        ll tmp = n;
        for (int p : primes) {
            if (p > tmp) break;
            if (tmp % p == 0) {
                cnt++;
                while (tmp % p == 0) tmp /= p;
            }
        }
        if (cnt >= 4) ans++;
    }

    cout << ans << "\n";
    return 0;
}
