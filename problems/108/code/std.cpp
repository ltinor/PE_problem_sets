#include<bits/stdc++.h>
using namespace std;
#define ll long long

// SPF sieve: smallest prime factor
const int MAXN = 500000;
int spf[MAXN + 1];
vector<int> primes;

void init_sieve() {
    for (int i = 2; i <= MAXN; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || (ll)i * p > MAXN) break;
            spf[i * p] = p;
        }
    }
}

// Count divisors of n^2: d(n^2) = prod(2*e_i + 1)
ll count_solutions(ll n) {
    ll ans = 1;
    while (n > 1) {
        int p = spf[n];
        int e = 0;
        while (n % p == 0) {
            n /= p;
            e++;
        }
        ans *= (2 * e + 1);
    }
    // Number of distinct solutions = (d(n^2) + 1) / 2
    return (ans + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init_sieve();

    ll K;
    cin >> K;

    for (ll n = 1; ; n++) {
        if (count_solutions(n) > K) {
            cout << n << "\n";
            break;
        }
    }

    return 0;
}
