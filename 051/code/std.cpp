#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXP = 5000000;
vector<bool> is_prime;
vector<int> primes;

void sieve(int n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}

bool isPrimeFast(int x) {
    if (x <= MAXP) return is_prime[x];
    if (x < 2) return false;
    for (int p : primes) {
        if ((ll)p * p > x) break;
        if (x % p == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve(MAXP);

    int K;
    cin >> K;

    // Search through precomputed primes first
    for (int p : primes) {
        string s = to_string(p);
        int L = s.size();
        int total_masks = (1 << L) - 1;
        for (int mask = 1; mask <= total_masks; mask++) {
            char base_digit = 0;
            bool ok = true;
            for (int i = 0; i < L; i++) {
                if (mask & (1 << i)) {
                    if (base_digit == 0) base_digit = s[i];
                    else if (s[i] != base_digit) { ok = false; break; }
                }
            }
            if (!ok) continue;

            bool leading_in_mask = (mask & 1);
            int cnt = 0;
            for (int d = 0; d <= 9; d++) {
                if (leading_in_mask && d == 0) continue;
                string t = s;
                for (int i = 0; i < L; i++) {
                    if (mask & (1 << i)) t[i] = '0' + d;
                }
                int val = stoi(t);
                if (isPrimeFast(val)) cnt++;
            }
            if (cnt == K) {
                cout << p << "\n";
                return 0;
            }
        }
    }

    // If not found, continue searching beyond precomputed primes
    for (int x = MAXP + 1; ; x++) {
        if (!isPrimeFast(x)) continue;
        string s = to_string(x);
        int L = s.size();
        int total_masks = (1 << L) - 1;
        for (int mask = 1; mask <= total_masks; mask++) {
            char base_digit = 0;
            bool ok = true;
            for (int i = 0; i < L; i++) {
                if (mask & (1 << i)) {
                    if (base_digit == 0) base_digit = s[i];
                    else if (s[i] != base_digit) { ok = false; break; }
                }
            }
            if (!ok) continue;

            bool leading_in_mask = (mask & 1);
            int cnt = 0;
            for (int d = 0; d <= 9; d++) {
                if (leading_in_mask && d == 0) continue;
                string t = s;
                for (int i = 0; i < L; i++) {
                    if (mask & (1 << i)) t[i] = '0' + d;
                }
                int val = stoi(t);
                if (isPrimeFast(val)) cnt++;
            }
            if (cnt == K) {
                cout << x << "\n";
                return 0;
            }
        }
    }
    return 0;
}
