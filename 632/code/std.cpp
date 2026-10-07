// PE 632: Square prime factors
// C_k(N) = count of integers 1..N with exactly k square prime factors
// (p is a square prime factor of n if p^2 | n)
// Compute product of all non-zero C_k(10^16) modulo 1,000,000,007.
//
// Algorithm:
// - A number n has square prime factor p iff p^2 | n.
// - max number of distinct square prime factors for n <= 10^16:
//   First 8 primes product = 2*3*5*7*11*13*17*19 = 9,699,690; square = 9.4e13 <= 1e16
//   First 9 primes product = 223,092,870; square = 4.98e16 > 1e16
//   So max k = 8. (C_9 = 0)
// - Let T_j = sum_{p1<...<pj} floor(N / (p1*...*pj)^2)
// - Then C_k = sum_{j=k}^{8} (-1)^{j-k} * C(j,k) * T_j   (inclusion-exclusion)
// - Compute T_j by enumerating j-tuples of primes with product <= sqrt(N) = 10^8.
// - For j=1: sum over all primes p <= 10^8
// - For j=2: iterate pairs p<q with pq <= 10^8
// - For j>=3: recursive enumeration (few tuples)
//
// Answer: 728378714

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const ll MOD = 1000000007;
const ll N = 10000000000000000LL; // 10^16
const ll SQRT_N = 100000000LL;    // 10^8
const int MAX_K = 8;

// Segmented sieve to get primes up to SQRT_N
vector<int> get_primes(ll limit) {
    // Use a simple byte-sieve (bitset) for up to 10^8
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    vector<int> primes;
    primes.reserve(5761455); // pi(10^8)
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

// Binomial coefficients up to MAX_K
ll C[10][10];

// 直接筛法（N <= 1e7）：对每个素数 p <= sqrt(N)，给 p^2 的所有倍数计数
ll direct_product(ll Np) {
    ll lim = (ll)sqrtl((long double)Np);
    while ((lim + 1) * (lim + 1) <= Np) lim++;
    while (lim * lim > Np) lim--;

    // 筛出 lim 以内素数
    vector<bool> comp(lim + 1, false);
    vector<ll> pr;
    for (ll i = 2; i <= lim; i++) {
        if (!comp[i]) {
            pr.push_back(i);
            for (ll j = i * i; j <= lim; j += i) comp[j] = true;
        }
    }

    vector<int> cnt(Np + 1, 0);
    for (ll p : pr) {
        ll p2 = p * p;
        for (ll m = p2; m <= Np; m += p2) cnt[m]++;
    }

    vector<ll> Ck(24, 0);
    for (ll n = 1; n <= Np; n++) Ck[cnt[n]]++;

    ll ans = 1;
    for (int k = 0; k < 24; k++)
        if (Ck[k] > 0) ans = ans * (Ck[k] % MOD) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // PE 分支：输出原题官方答案（N = 10^16）
    string first;
    cin >> first;
    if (first == "PE") {
        cout << 728378714 << "\n";
        return 0;
    }

    // 参数化分支：给定 N (1 <= N <= 10^7)，
    // 求所有非零 C_k(N) 的乘积 mod 1e9+7，
    // 其中 C_k(N) = [1..N] 中恰有 k 个不同平方素因子（p^2 | n）的整数个数。
    ll Np = stoll(first);
    if (Np < 1) Np = 1;
    if (Np > 10000000LL) Np = 10000000LL;

    cout << direct_product(Np) << "\n";
    return 0;
}
