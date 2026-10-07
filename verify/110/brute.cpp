#include<bits/stdc++.h>
using namespace std;
using i128 = __int128;

// Brute force for small K: enumerate n starting from 1
// Only works for K <= ~200 within reasonable time

const int MAXN = 1000000;
int spf[MAXN + 1];
vector<int> primes_list;

void init_sieve() {
    for (int i = 2; i <= MAXN; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes_list.push_back(i);
        }
        for (int p : primes_list) {
            if (p > spf[i] || (long long)i * p > MAXN) break;
            spf[i * p] = p;
        }
    }
}

i128 count_solutions(long long n) {
    i128 ans = 1;
    while (n > 1) {
        int p = spf[n];
        int e = 0;
        while (n % p == 0) {
            n /= p;
            e++;
        }
        ans *= (2 * e + 1);
    }
    // solutions = (d(n^2) + 1) / 2
    return (ans + 1) / 2;
}

void print_i128(i128 x) {
    if (x == 0) { cout << "0"; return; }
    if (x < 0) { cout << "-"; x = -x; }
    string s;
    while (x > 0) { s += char('0' + (x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init_sieve();

    long long K;
    cin >> K;

    for (long long n = 1; n <= MAXN; n++) {
        if (count_solutions(n) > K) {
            cout << n << "\n";
            return 0;
        }
    }

    // If not found within range (K too large for brute), output -1
    cout << "-1\n";
    return 0;
}
