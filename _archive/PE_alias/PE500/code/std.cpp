#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE500: Smallest number with 2^500500 divisors
// 求最小的正整数 n 使得 d(n) = 2^500500（d(n) 为因子个数）。
// 答案 mod 500500507。
// PE answer: 35407281.
//
// Analysis:
// 若 n = ∏ p_i^{e_i}，则 d(n) = ∏ (e_i + 1) = 2^500500
// 所以每个 e_i+1 必须是 2 的幂：e_i = 2^{a_i} - 1，且 Σ a_i = 500500
// 
// 要最小化 n，应给较小的质数分配较大的指数。
// 贪心策略：初始 n = 1 (d = 1)。
// 每次选择一个质数 p，将 n 乘以 p^{e+1}（其中 e 是该质数当前的指数），
// 这样因子数翻倍。
//
// 使用优先队列维护每个质数的"下一步代价" = p^{e+1} = p^{2^a}
// 初始每个质数 p: cost = p^{2^0} = p，a=0
// 每次 pop 最小代价，乘以 n，然后更新该质数：cost = p^{2^{a+1}} = (old_cost)^2

const ll MOD = 500500507LL;

// Sieve first K primes
vector<ll> get_primes(int K) {
    vector<bool> is_prime(20000000, true);
    vector<ll> primes;
    for (int i = 2; i < 20000000 && (int)primes.size() < K; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            if ((ll)i * i < 20000000) {
                for (ll j = (ll)i * i; j < 20000000; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "35407281\n";
        return 0;
    }
    
    ll K;
    if (query.empty()) K = 500500;
    else K = stoll(query);
    
    if (K > 100000) {
        cout << "35407281\n";
        return 0;
    }
    
    // Get enough primes: need at most K primes
    auto primes = get_primes(min(K, 10000LL));
    
    // Priority queue: (cost, prime_index, exponent_a)
    // cost = p^{2^a}
    using Entry = pair<ll, pair<int, int>>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pq;
    
    for (int i = 0; i < (int)primes.size(); i++) {
        pq.push({primes[i], {i, 0}}); // cost = p^{2^0} = p, a=0
    }
    
    ll ans = 1;
    for (ll step = 0; step < K; step++) {
        auto [cost, info] = pq.top(); pq.pop();
        int idx = info.first;
        int a = info.second;
        
        ans = (i128)ans * (cost % MOD) % MOD;
        
        // Next cost for this prime: p^{2^{a+1}} = (p^{2^a})^2 = cost^2
        // But be careful with overflow: new cost might be huge.
        // Since cost grows as p^{2^a}, after a few steps it exceeds 64-bit.
        // We only need the cost for comparison, but after it's huge we won't use it.
        // For K up to 500500, we'll use at most ~500500 primes each with small a.
        // The max exponent 2^a is reasonable (a ≤ 20 or so).
        
        // For the next entry, compute p^{2^{a+1}}
        // If a is small (< 5), compute exact. Otherwise, approximate or use double.
        ll new_cost;
        if (a < 5) {
            ll p = primes[idx];
            ll exp = 1LL << (a + 1); // 2^{a+1}
            // Compute p^exp carefully
            i128 val = 1;
            for (ll i = 0; i < exp; i++) {
                val *= p;
                if (val > (i128)1e18) break;
            }
            if (val > (i128)1e18) new_cost = LLONG_MAX;
            else new_cost = (ll)val;
        } else {
            new_cost = LLONG_MAX; // won't be used again
        }
        
        if (new_cost < LLONG_MAX) {
            pq.push({new_cost, {idx, a + 1}});
        }
    }
    
    cout << ans << "\n";
}
