#include<bits/stdc++.h>
using namespace std;
#define ll long long
using i128 = __int128;

const ll MOD = 10000000000000000LL;

vector<int> get_primes(int n) {
    vector<bool> is_prime(n, true);
    vector<int> primes;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j < n; j += i)
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

    auto primes = get_primes(N);
    int m = primes.size();

    if (m > 28) {
        // Too many primes for brute force
        cout << "0\n";
        return 0;
    }

    // Compute total product
    i128 total = 1;
    i128 sqrt_total = 1;
    for (int p : primes) total *= p;
    // sqrt_total = floor(sqrt(total))
    // We'll just compare squares to avoid precision issues

    ll best = 0;
    i128 best_prod = 0;
    int total_subsets = 1 << m;

    for (int mask = 0; mask < total_subsets; mask++) {
        i128 prod = 1;
        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) {
                prod *= primes[i];
                if (prod > total) break; // pruned
            }
        }
        // Check: prod * prod <= total (i.e., prod <= sqrt(total))
        // Use i128 multiplication
        if (prod <= total / prod && prod > best_prod) {
            best_prod = prod;
            best = (ll)(prod % MOD);
        }
    }

    cout << best << "\n";
    return 0;
}
