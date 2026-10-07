#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; (ll)i * i <= x; i += 2)
        if (x % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    // Search primes by generating them on the fly
    for (int x = 2; ; x++) {
        if (!isPrime(x)) continue;
        string s = to_string(x);
        int L = s.size();
        int total_masks = (1 << L) - 1;
        for (int mask = 1; mask <= total_masks; mask++) {
            // All masked positions must have the SAME original digit
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
                    if (mask & (1 << i)) {
                        t[i] = '0' + d;
                    }
                }
                int val = stoi(t);
                if (isPrime(val)) cnt++;
            }
            if (cnt == K) {
                cout << x << "\n";
                return 0;
            }
        }
    }
    return 0;
}
