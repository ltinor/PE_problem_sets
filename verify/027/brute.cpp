#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime_naive(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

int count_primes(int a, int b) {
    int n = 0;
    while (true) {
        int val = n * n + a * n + b;
        if (val < 2 || !is_prime_naive(val)) break;
        n++;
    }
    return n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int A, B;
        cin >> A >> B;

        int best_len = 0;
        ll best_prod = 0;

        for (int a = -(A - 1); a <= A - 1; a++) {
            for (int b = -B; b <= B; b++) {
                if (!is_prime_naive(abs(b))) continue;
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
