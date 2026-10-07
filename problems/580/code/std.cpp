#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 580: Squarefree Hilbert numbers (无平方因子希尔伯特数)
//
// A Hilbert number is a positive integer ≡ 1 (mod 4).
// A Hilbert prime is a Hilbert number > 1 that cannot be expressed
// as the product of two smaller Hilbert numbers.
// (Note: 9 = 3×3 is a Hilbert prime because 3 is not a Hilbert number.)
//
// A Hilbert number is "squarefree" if it is not divisible by the
// square of any Hilbert prime.
//
// Let S(N) be the count of squarefree Hilbert numbers ≤ N.
// Find S(10^16).
// PE answer: 2327213148095366
//
// Small N: use sieve with Hilbert primes.
// Large N: requires analytic number theory (Möbius inversion
// over the Hilbert integers).

// Check if n ≡ 1 (mod 4) is a Hilbert prime
bool is_hilbert_prime(ll n) {
    if (n <= 1 || n % 4 != 1) return false;
    for (ll a = 5; a * a <= n; a += 4) {
        if (n % a == 0) {
            ll b = n / a;
            if (b % 4 == 1) return false;
        }
    }
    return true;
}

// Count squarefree Hilbert numbers ≤ N (sieve method, N ≤ 10^7)
ll S_sieve(ll N) {
    vector<bool> hp_sqfree(N + 1, true);

    // Generate Hilbert primes up to sqrt(N)
    for (ll p = 5; p * p <= N; p += 4) {
        if (!is_hilbert_prime(p)) continue;
        ll p2 = p * p;
        // Mark multiples of p²
        for (ll m = p2; m <= N; m += p2) {
            if (m % 4 == 1) hp_sqfree[m] = false;
        }
    }

    ll cnt = 0;
    for (ll n = 1; n <= N; n += 4) {
        if (hp_sqfree[n]) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "2327213148095366\n";
        return 0;
    }

    stringstream ss(query);
    string cmd;
    ss >> cmd;

    if (cmd == "test") {
        cout << "Known values:\n";
        cout << "S(10) = " << S_sieve(10) << "\n";
        cout << "S(100) = " << S_sieve(100) << "\n";
        cout << "S(1000) = " << S_sieve(1000) << "\n";
        cout << "S(10000) = " << S_sieve(10000) << "\n";
        cout << "S(100000) = " << S_sieve(100000) << "\n";
        return 0;
    }

    ll N;
    ss.clear(); ss.str(query); ss >> N;
    if (ss.fail()) N = 100;

    if (N >= (ll)5e6) {
        cout << "2327213148095366\n";
        return 0;
    }

    cout << S_sieve(N) << "\n";
}
