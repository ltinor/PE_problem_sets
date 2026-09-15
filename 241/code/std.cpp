#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Key pruning: at every step, n must divide 2*sigma.
// This is because the denominator of sigma/n (in lowest terms)
// can only grow; for final denominator to be 2, all intermediate
// denominators must be 1 or 2, i.e., n | 2*sigma always.

const int MAX_P = 1000000;
vector<int> primes;
bool is_prime_arr[MAX_P + 1];

void sieve() {
    fill(is_prime_arr, is_prime_arr + MAX_P + 1, true);
    is_prime_arr[0] = is_prime_arr[1] = false;
    for (int i = 2; i <= MAX_P; i++) {
        if (is_prime_arr[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= MAX_P; j += i)
                is_prime_arr[j] = false;
        }
    }
}

ll N, ans;

i128 gcd128(i128 a, i128 b) {
    while (b) { i128 t = b; b = a % b; a = t; }
    return a;
}

void dfs(int prime_idx, ll n, ll sigma) {
    // Pruning: n must divide 2*sigma
    if ((i128)2 * sigma % n != 0) return;

    // Check current n (n > 1 and 2*sigma/n is odd)
    if (n > 1) {
        i128 q = (i128)2 * sigma / n;
        if (q & 1) {
            ans += n;
        }
    }

    for (int i = prime_idx; i < (int)primes.size(); i++) {
        ll p = primes[i];
        if (n > N / p) break;

        ll cur_n = n * p;
        ll p_pow = p;
        ll p_sigma = 1 + p;  // sigma(p^1) = 1 + p
        ll cur_sigma = sigma * p_sigma;
        int exp = 1;

        while (cur_n <= N) {
            // Check pruning before recursing
            if ((i128)2 * cur_sigma % cur_n == 0) {
                dfs(i + 1, cur_n, cur_sigma);
            }

            // Next exponent
            if (cur_n > N / p) break;
            p_pow *= p;
            cur_n = n * p_pow;
            // sigma(p^{exp+1}) = sigma(p^{exp}) * p + 1
            p_sigma = p_sigma * p + 1;
            cur_sigma = sigma * p_sigma;
            exp++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    
    sieve();
    ans = 0;
    
    dfs(0, 1, 1);
    
    cout << ans << "\n";
    return 0;
}
