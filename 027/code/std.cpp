#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX_N = 2001000; // enough for A,B <= 1000: worst case prime check up to ~1000*1000+1000
bool is_prime[MAX_N];

void sieve(int n) {
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}

int count_primes(int a, int b) {
    int n = 0;
    while (true) {
        int val = n * n + a * n + b;
        if (val < 2 || !is_prime[val]) break;
        n++;
    }
    return n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve(MAX_N - 1);

    int T;
    cin >> T;
    while (T--) {
        int A, B;
        cin >> A >> B;
        // A, B <= 1000
        int best_len = 0;
        ll best_prod = 0;

        for (int a = -(A - 1); a <= A - 1; a++) {
            for (int b = -B; b <= B; b++) {
                if (!is_prime[abs(b)]) continue; // b must be prime for n=0
                int len = count_primes(a, b);
                if (len > best_len) {
                    best_len = len;
                    best_prod = (ll)a * b;
                }
            }
        }
        cout << best_prod << "\n";
    }
    return 0;
}
