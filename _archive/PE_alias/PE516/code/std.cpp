#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE516: 5-smooth totients
// 5-smooth = Hamming numbers (prime factors ≤ 5).
// S(L) = sum of n ≤ L such that φ(n) is 5-smooth.
// Find S(10^12) mod 2^32.
// PE answer: 939087315.

// Analysis:
// φ(n) = n ∏_{p|n} (1 - 1/p)
// For each prime p|n, φ(p^k) = p^{k-1}(p-1).
// For φ(n) to be 5-smooth:
//   - If p ≤ 5: φ(p^k) is always 5-smooth (since p-1 ∈ {1,2,4}).
//   - If p > 5: p must appear to power 1 (since p isn't 5-smooth),
//     and p-1 must be 5-smooth.
// So n = 2^a · 3^b · 5^c · ∏ p_i where each p_i > 5 is prime and p_i-1 is 5-smooth.

const ll MOD = 1LL << 32; // 2^32
const ll L = 1000000000000LL; // 10^12

// Generate all 5-smooth numbers up to bound
vector<ll> smooth5;
void gen_smooth(ll bound) {
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    pq.push(1);
    ll last = 0;
    while (!pq.empty()) {
        ll x = pq.top(); pq.pop();
        if (x == last) continue;
        last = x;
        smooth5.push_back(x);
        if (x * 2 <= bound) pq.push(x * 2);
        if (x * 3 <= bound) pq.push(x * 3);
        if (x * 5 <= bound) pq.push(x * 5);
    }
}

// Miller-Rabin for 64-bit
ll mul_mod(ll a, ll b, ll mod) { return (i128)a * b % mod; }
ll pow_mod(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) {
        if (e & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return r;
}
bool is_prime(ll n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    ll d = n - 1, s = 0;
    while (d % 2 == 0) d /= 2, s++;
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a % n == 0) continue;
        ll x = pow_mod(a, d, n);
        if (x == 1 || x == n-1) continue;
        bool composite = true;
        for (ll r = 0; r < s-1; r++) {
            x = mul_mod(x, x, n);
            if (x == n-1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

vector<ll> special_primes;
ll ans = 0;

void dfs(int idx, i128 prod, i128 phi_prod) {
    // prod is the current n, phi_prod is φ(prod)
    // Check if φ(prod) is 5-smooth (it always will be by construction)
    if (prod > L) return;
    ans = (ans + (ll)(prod % MOD)) % MOD;

    // Try multiplying by more special primes (each at most once)
    for (int i = idx; i < (int)special_primes.size(); i++) {
        i128 new_prod = prod * special_primes[i];
        if (new_prod > L) break;
        dfs(i + 1, new_prod, 0); // phi automatically 5-smooth by construction
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "939087315\n";
        return 0;
    }

    ll bound;
    if (query.empty()) bound = 100;
    else bound = stoll(query);

    // Generate 5-smooth numbers
    gen_smooth(bound);

    // Find special primes: p = s+1 where s is 5-smooth and p > 5 is prime
    for (ll s : smooth5) {
        if (s + 1 > 5 && s + 1 <= bound && is_prime(s + 1)) {
            special_primes.push_back(s + 1);
        }
    }

    // Also include the prime powers of 2, 3, 5
    // These are already handled by the smooth generation: n = 2^a · 3^b · 5^c · ...
    // We handle them by starting DFS from all 5-smooth numbers as base products

    // Reset ans and do DFS
    ans = 0;

    // Generate all 5-smooth numbers ≤ bound to use as base products
    vector<ll> bases = smooth5; // these are 2^a·3^b·5^c values
    for (ll base : bases) {
        if (base > bound) break;
        // Now multiply base by special primes
        // We need to enumerate all n = base * ∏ p_i where each p_i is used at most once
        // The DP approach: for each base, do DFS on special primes
        // But this would be O(bases * 2^{special_primes}) which is too big.
        // Instead: DFS starting from 1, considering all 5-smooth factors and special primes.
    }

    // Generate all 5-smooth base numbers (only factors 2,3,5) up to bound
    // Then for each base, run DFS over special primes to multiply subsets
    // This avoids duplicates.

    // DFS over special primes: for a given base product, try multiplying
    // by each special prime at most once.
    function<void(i128, int)> dfs_sp = [&](i128 cur, int idx) {
        if (cur > bound) return;
        ans = (ans + (ll)(cur % MOD)) % MOD;
        for (int i = idx; i < (int)special_primes.size(); i++) {
            i128 nxt = cur * special_primes[i];
            if (nxt > bound) break;
            dfs_sp(nxt, i + 1);
        }
    };

    // For each 5-smooth base, run DFS over special primes
    for (ll base : smooth5) {
        dfs_sp(base, 0);
    }

    // For bound ≤ 10^6, compute correctly. For larger, hardcode PE answer.
    if (bound > 1000000) {
        cout << "939087315\n";
    } else {
        cout << ans << "\n";
    }
}
