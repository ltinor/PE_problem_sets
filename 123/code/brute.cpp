#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// Brute force: compute (p-1)^n + (p+1)^n mod p^2 directly
vector<int> gen_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = 1LL * i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    return primes;
}

ull mod_pow(ull base, ull exp, ull mod) {
    ull result = 1;
    base %= mod;
    while (exp) {
        if (exp & 1) result = (__int128)result * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ull T;
    cin >> T;

    vector<int> primes = gen_primes(5000000);

    for (int n = 1; n <= (int)primes.size(); n++) {
        ull p = primes[n - 1];
        ull p2 = p * p;
        ull left = mod_pow(p - 1, n, p2);
        ull right = mod_pow(p + 1, n, p2);
        ull r = (left + right) % p2;
        if (r > T) {
            cout << n << "\n";
            return 0;
        }
    }

    return 0;
}
