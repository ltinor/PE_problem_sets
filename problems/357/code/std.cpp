#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE357: Sum of n <= N such that for every divisor d of n, d+n/d is prime.
// Key: n+1 must be prime (d=1). n must be even (since n+1 is prime > 2).
// n must be squarefree: if p^2|n then p + n/p is composite (divisible by p and > p).
// So n = 2 * product of distinct odd primes.
// For each divisor d, d + n/d must be prime.
// Build recursively: start with n=2, multiply by primes p where n*p <= N
// and all divisor checks pass.

const ll MAXN = 100000000;

vector<bool> is_prime;
vector<ll> primes;

void sieve(ll n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    for (ll i = 2; i <= n; i++)
        if (is_prime[i]) primes.push_back(i);
}

vector<ll> divisors(ll n) {
    vector<ll> divs;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divs.push_back(d);
            if (d * d != n) divs.push_back(n / d);
        }
    }
    return divs;
}

bool check_all_divisors(ll n) {
    for (ll d : divisors(n)) {
        if (!is_prime[d + n / d]) return false;
    }
    return true;
}

// Recursive DFS building n from primes
ll total_sum = 0;
ll N;

void dfs(size_t idx, ll cur_n, ll max_n) {
    if (cur_n > max_n) return;
    
    if (cur_n > 2 && check_all_divisors(cur_n)) {
        total_sum += cur_n;
    }
    
    for (size_t i = idx; i < primes.size(); i++) {
        ll p = primes[i];
        if (cur_n * p > max_n) break;
        // p must not divide cur_n (squarefree)
        if (cur_n % p == 0) continue;
        dfs(i + 1, cur_n * p, max_n);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    
    if (N > 100000000) N = 100000000;
    if (N <= 2) { cout << "0\n"; return 0; }
    
    // For small N, check all even numbers
    if (N <= 1000000) {
        sieve(N + 1);
        ll ans = 0;
        for (ll n = 2; n <= N; n += 2) {
            if (!is_prime[n + 1]) continue;
            bool ok = true;
            for (ll d = 1; d * d <= n; d++) {
                if (n % d == 0) {
                    if (!is_prime[d + n / d]) { ok = false; break; }
                    ll d2 = n / d;
                    if (d2 != d && !is_prime[d2 + n / d2]) { ok = false; break; }
                }
            }
            if (ok) ans += n;
        }
        cout << ans << "\n";
        return 0;
    }
    
    // For large N up to 10^8, use DFS over primes
    sieve(N + 1);
    
    // Start with n=2
    if (check_all_divisors(2)) total_sum = 2;
    
    // DFS: multiply by increasing primes
    // Need primes up to N/2 (since we start with 2)
    dfs(1, 2, N); // start from index 1 (prime 3)
    
    cout << total_sum << "\n";
    return 0;
}
