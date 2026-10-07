#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 158: Strings with One Lexicographic Ascent
// p(n) = C(26, n) * (2^n - n - 1)
// Find max p(n) for n=1..26

// Compute C(n, k) using 128-bit or careful overflow handling
// C(26, n) max is C(26, 13) ≈ 10,400,600
// 2^n max is 2^26 ≈ 67 million
// So p(n) max is about 10^7 * 67*10^6 ≈ 7*10^14, fits in 64-bit

ll comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    ll res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Fixed answer problem: input dummy, output max p(n)
    int dummy;
    cin >> dummy;

    ll max_p = 0;
    int best_n = 0;

    for (int n = 1; n <= 26; n++) {
        ll c = comb(26, n);
        ll pow2 = (1LL << n) - n - 1;
        ll p = c * pow2;
        if (p > max_p) {
            max_p = p;
            best_n = n;
        }
    }

    cout << max_p << "\n";
    return 0;
}
