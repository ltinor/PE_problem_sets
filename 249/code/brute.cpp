#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 10000000000000000LL; // 10^16

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> primes;
    for (int i = 2; i < N; i++)
        if (is_prime(i)) primes.push_back(i);

    int m = (int)primes.size();
    ll ans = 0;

    int total = 1 << m;
    for (int mask = 1; mask < total; mask++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            if (mask & (1 << j))
                sum += primes[j];
        }
        if (is_prime(sum))
            ans = (ans + 1) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
