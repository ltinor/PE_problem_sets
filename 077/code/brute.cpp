#include<bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> get_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    int n = 2;
    while (true) {
        vector<int> primes = get_primes(n);
        vector<ll> dp(n + 1, 0);
        dp[0] = 1;
        for (int p : primes) {
            for (int x = p; x <= n; x++) {
                dp[x] += dp[x - p];
            }
        }
        if (dp[n] > K) {
            cout << n << "\n";
            break;
        }
        n++;
    }

    return 0;
}
