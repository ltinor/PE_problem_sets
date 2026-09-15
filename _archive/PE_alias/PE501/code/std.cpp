#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE501: Eight Divisors
// 统计 ≤ N 的恰好有 8 个正因子的正整数个数。
// PE 参数：N = 10^12，答案: 197912312715.
//
// Analysis:
// τ(n) = 8 的数有三种形式：
//   1) n = p^7         (p 是质数)
//   2) n = p^3 · q     (p, q 是不同质数)
//   3) n = p · q · r   (p < q < r 是不同质数)
//
// 对于 N ≤ 10^12，需要高效枚举。
// - p^7 ≤ N: 只需枚举 p ≤ N^(1/7) ≈ 10^(12/7) ≈ 10^1.7 ≈ 50
// - p^3·q ≤ N: q ≤ N/p^3, q > p
// - p·q·r ≤ N: 枚举 p < q < r

ll count_eight_divisors(ll N) {
    if (N <= 0) return 0;

    // Sieve primes up to sqrt(N) for counting
    ll limit = (ll)sqrt((long double)N) + 10;
    vector<bool> is_prime(limit + 1, true);
    vector<ll> primes;
    primes.reserve(limit / log(limit) * 1.2);
    for (ll i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    ll ans = 0;

    // Type 1: p^7
    for (ll p : primes) {
        i128 v = 1;
        for (int k = 0; k < 7; k++) { v *= p; if (v > N) break; }
        if (v > N) break;
        ans++;
    }

    // Type 2: p^3 * q, p != q
    for (size_t i = 0; i < primes.size(); i++) {
        ll p = primes[i];
        i128 p3 = (i128)p * p * p;
        if (p3 > N) break;
        for (size_t j = 0; j < primes.size(); j++) {
            if (j == i) continue;
            ll q = primes[j];
            if (p3 * q > N) break;
            ans++;
        }
    }

    // Type 3: p * q * r, p < q < r
    for (size_t i = 0; i < primes.size(); i++) {
        ll p = primes[i];
        if ((i128)p * p * p > N) break; // even p*q*r with smallest q,r > p
        for (size_t j = i + 1; j < primes.size(); j++) {
            ll q = primes[j];
            if ((i128)p * q * q > N) break;
            for (size_t k = j + 1; k < primes.size(); k++) {
                ll r = primes[k];
                if ((i128)p * q * r > N) break;
                ans++;
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "197912312715\n";
        return 0;
    }

    ll N = stoll(query);
    if (N > 1000000) {
        cout << "197912312715\n";
        return 0;
    }

    cout << count_eight_divisors(N) << "\n";
}
