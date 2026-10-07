#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int digit_sum(ull x) {
    int s = 0;
    while (x) { s += x % 10; x /= 10; }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute all digit-power-sum numbers
    vector<ull> results;
    // Maximum number needed: a_30 ≈ 2.48e14, digit sums up to ~9*15=135
    for (int s = 2; s <= 200; s++) {
        ull p = s;
        for (int e = 2; ; e++) {
            // Check overflow before multiplying
            if (p > 18000000000000000000ULL / s) break;
            p *= s;
            if (p < 10) continue;  // need at least 2 digits
            if (digit_sum(p) == s) {
                results.push_back(p);
            }
        }
    }
    sort(results.begin(), results.end());

    int K;
    cin >> K;
    cout << results[K - 1] << "\n";
    return 0;
}
