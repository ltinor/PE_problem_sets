#include<bits/stdc++.h>
using namespace std;
#define ll long long
using i128 = __int128;

const ll MOD = 10000000000000000LL; // 10^16

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

    // Compute total log product
    long double total_log = 0;
    for (int p : primes) total_log += logl(p);
    long double target_log = total_log / 2.0L;

    // Split primes into two halves
    int mid = m / 2;

    // Generate left half subsets
    vector<pair<long double, ll>> left;
    int left_cnt = 1 << mid;
    left.reserve(left_cnt);
    for (int mask = 0; mask < left_cnt; mask++) {
        long double cur_log = 0;
        ll cur_mod = 1;
        for (int i = 0; i < mid; i++) {
            if (mask & (1 << i)) {
                cur_log += logl(primes[i]);
                cur_mod = (i128)cur_mod * primes[i] % MOD;
            }
        }
        left.push_back({cur_log, cur_mod});
    }
    sort(left.begin(), left.end());

    // Extract sorted arrays
    vector<long double> left_logs;
    vector<ll> left_mods;
    left_logs.reserve(left.size());
    left_mods.reserve(left.size());
    for (auto& p : left) {
        left_logs.push_back(p.first);
        left_mods.push_back(p.second);
    }

    // Generate right half subsets and search
    int right_cnt = 1 << (m - mid);
    long double best_log = -1;
    ll best_mod = 0;

    for (int mask = 0; mask < right_cnt; mask++) {
        long double cur_log = 0;
        ll cur_mod = 1;
        for (int i = 0; i < m - mid; i++) {
            if (mask & (1 << i)) {
                cur_log += logl(primes[mid + i]);
                cur_mod = (i128)cur_mod * primes[mid + i] % MOD;
            }
        }

        long double need = target_log - cur_log;
        if (need < 0) continue;

        auto it = upper_bound(left_logs.begin(), left_logs.end(), need);
        if (it == left_logs.begin()) continue;
        --it;

        long double total = *it + cur_log;
        if (total > best_log) {
            best_log = total;
            int idx = it - left_logs.begin();
            best_mod = (i128)left_mods[idx] * cur_mod % MOD;
        }
    }

    cout << best_mod << "\n";
    return 0;
}
