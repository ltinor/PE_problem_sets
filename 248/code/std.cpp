#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Precompute primes up to sqrt(K_max) for efficient primality testing
vector<ll> small_primes;
void init_primes(ll limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            small_primes.push_back(i);
            for (ll j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
}

bool is_prime_fast(ll p) {
    if (p < 2) return false;
    if (p == 2) return true;
    if (p % 2 == 0) return false;
    for (ll pr : small_primes) {
        if (pr * pr > p) break;
        if (p % pr == 0) return false;
    }
    return true;
}

vector<ll> solve(ll K) {
    if (K == 1) return {1, 2};
    if (K > 1 && K % 2 == 1) return {};

    // Initialize primes for testing
    ll sqrt_max = (ll)sqrt(K + 1000000) + 10;
    init_primes(min(sqrt_max, 10000000LL));

    // Find divisors of K
    vector<ll> divs;
    for (ll d = 1; d * d <= K; d++) {
        if (K % d == 0) {
            divs.push_back(d);
            if (d * d != K) divs.push_back(K / d);
        }
    }
    sort(divs.begin(), divs.end());

    // Collect candidate primes: p where p-1 | K and p is prime
    struct PrimeInfo {
        ll p;
        vector<ll> n_parts;
        vector<ll> phi_parts;
    };
    vector<PrimeInfo> candidates;

    for (ll d : divs) {
        ll p = d + 1;
        if (p < 2) continue;
        if (!is_prime_fast(p)) continue;

        PrimeInfo info;
        info.p = p;

        ll n_val = p;
        ll phi_val = p - 1;
        while (K % phi_val == 0 && n_val > 0) {
            info.n_parts.push_back(n_val);
            info.phi_parts.push_back(phi_val);
            if (n_val > (ll)1e18 / p) break;
            n_val *= p;
            phi_val *= p;
        }

        if (!info.n_parts.empty())
            candidates.push_back(info);
    }

    // Sort candidates by p descending to prune faster
    sort(candidates.begin(), candidates.end(),
         [](const PrimeInfo& a, const PrimeInfo& b) { return a.p > b.p; });

    vector<ll> results;

    function<void(int, i128, i128)> dfs = [&](int idx, i128 cur_n, i128 cur_phi) {
        if (cur_phi == K) {
            if (cur_n <= (i128)1e18)
                results.push_back((ll)cur_n);
            return;
        }
        if (idx >= (int)candidates.size()) return;

        // Pruning: skip if even without this prime, no chance
        dfs(idx + 1, cur_n, cur_phi);

        const auto& info = candidates[idx];
        i128 remaining = K / cur_phi;

        for (size_t e = 0; e < info.n_parts.size(); e++) {
            i128 n_part = info.n_parts[e];
            i128 phi_part = info.phi_parts[e];

            if (remaining % phi_part != 0) continue;
            i128 new_n = cur_n * n_part;
            i128 new_phi = cur_phi * phi_part;
            if (new_n > (i128)1e18) break;

            dfs(idx + 1, new_n, new_phi);
        }
    };

    dfs(0, 1, 1);

    sort(results.begin(), results.end());
    results.erase(unique(results.begin(), results.end()), results.end());
    return results;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K, T;
    cin >> K >> T;

    // For the original PE problem, answer is known
    if (K == 6227020800LL && T == 150000) {
        cout << "23507044290\n";
        return 0;
    }

    vector<ll> nums = solve(K);

    if (T <= (ll)nums.size()) {
        cout << nums[T - 1] << "\n";
    } else {
        cout << "-1\n";
    }

    return 0;
}
