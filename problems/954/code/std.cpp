#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 954 (simple/reduced version): Heptaphobia / 恐七数
//
// A positive integer is "heptaphobic" if:
//   - it is NOT divisible by 7, and
//   - no number divisible by 7 can be produced by swapping two of its digits.
// Leading zeros are not allowed before or after the swap.
//
// C(N) = count of heptaphobic numbers < N.
//
// Reduced version: read a single integer N (N <= 10^7), output C(N).
// Simple O(N * d^2) brute force, where d = number of digits.

// 10^k mod 7 (needed for exponents up to ~20)
int pw[64];

// Check a single number in O(d^2).
bool is_heptaphobic(ll n) {
    if (n % 7 == 0) return false;
    string s = to_string(n);
    int d = (int)s.size();
    ll V = n % 7;

    for (int i = 0; i < d; i++) {
        for (int j = i + 1; j < d; j++) {
            if (s[i] == s[j]) continue;        // swap changes nothing
            if (i == 0 && s[j] == '0') continue; // would create a leading zero

            int ai = s[i] - '0', aj = s[j] - '0';
            // weights: 10^(d-1-i) and 10^(d-1-j) mod 7
            int wi = pw[d - 1 - i], wj = pw[d - 1 - j];
            // change of value (mod 7) caused by swapping positions i and j
            int delta = (aj - ai) * wi + (ai - aj) * wj;
            delta %= 7;
            if (delta < 0) delta += 7;

            if ((V + delta) % 7 == 0) return false; // swap produced a multiple of 7
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pw[0] = 1;
    for (int k = 1; k < 64; k++) pw[k] = pw[k - 1] * 10 % 7;

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll n = 1; n < N; n++) {
        if (is_heptaphobic(n)) ans++;
    }
    cout << ans << "\n";
    return 0;
}
