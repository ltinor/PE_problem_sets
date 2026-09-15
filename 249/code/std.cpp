#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 10000000000000000LL; // 10^16

vector<int> get_primes(int n) {
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> primes = get_primes(N - 1);
    int sum_all = 0;
    for (int p : primes) sum_all += p;

    // DP over subset sums -- only care about prime sums
    // Use bitset for DP to save memory
    vector<ll> dp(sum_all + 1, 0);
    dp[0] = 1;

    for (int p : primes) {
        for (int s = sum_all; s >= p; s--) {
            dp[s] = (dp[s] + dp[s - p]) % MOD;
        }
    }

    // Determine which sums are prime
    vector<bool> is_prime_sum(sum_all + 1, true);
    is_prime_sum[0] = is_prime_sum[1] = false;
    for (int i = 2; i * i <= sum_all; i++) {
        if (is_prime_sum[i]) {
            for (int j = i * i; j <= sum_all; j += i)
                is_prime_sum[j] = false;
        }
    }

    ll ans = 0;
    for (int s = 2; s <= sum_all; s++) {
        if (is_prime_sum[s]) {
            ans = (ans + dp[s]) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
