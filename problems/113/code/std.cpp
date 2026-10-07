#include <bits/stdc++.h>
using namespace std;
typedef __int128 i128;

// Print __int128
void print_i128(i128 x) {
    if (x == 0) { cout << "0"; return; }
    if (x < 0) { cout << "-"; x = -x; }
    string s;
    while (x > 0) { s += (char)('0' + (int)(x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

// Binomial coefficient C(n, k) using __int128
i128 C(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    i128 res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    // Increasing: choose D digits from 1..9 with repetition → C(D+9, 9) - 1 (exclude all zeros)
    i128 inc = C(D + 9, 9) - 1;

    // Decreasing: choose D digits from 0..9 with repetition → C(D+10, 10) - 1 (exclude all zeros)
    // But also exclude those that are only zeros: subtract D (all combinations of leading zeros
    // actually aren't valid numbers). Formula: C(D+10,10) - D - 1
    i128 dec = C(D + 10, 10) - D - 1;

    // Overlap: numbers where all digits are the same (111..., 222..., ..., 999...)
    // For each length 1..D, there are 9 such numbers → 9*D total
    i128 overlap = 9;
    overlap = overlap * D;

    i128 ans = inc + dec - overlap;
    print_i128(ans);
    cout << "\n";

    return 0;
}
