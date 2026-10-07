#include<bits/stdc++.h>
using namespace std;
typedef long double ld;

// Brute force: binary search using direct summation (no closed form)
// Used for verification against std

ld direct_sum(ld r, int n) {
    ld sum = 0.0L;
    for (int k = 1; k <= n; k++) {
        ld term = (900.0L - 3.0L * k);
        sum += term * powl(r, k - 1);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ld target;
    cin >> n >> target;

    ld s1 = 900.0L * n - 1.5L * n * (n + 1);

    if (fabsl(target - s1) < 1e-12L) {
        cout << fixed << setprecision(12) << 1.0L << "\n";
        return 0;
    }

    ld lo, hi;
    if (target < s1) {
        lo = 1.0L;
        hi = 2.0L;
        while (direct_sum(hi, n) > target) hi *= 1.5L;
    } else {
        lo = 0.0L;
        hi = 1.0L;
    }

    for (int iter = 0; iter < 80; iter++) {
        ld mid = (lo + hi) / 2.0L;
        ld smid = direct_sum(mid, n);
        if (target < s1) {
            if (smid < target) hi = mid;
            else lo = mid;
        } else {
            if (smid < target) lo = mid;
            else hi = mid;
        }
    }

    cout << fixed << setprecision(12) << (lo + hi) / 2.0L << "\n";
    return 0;
}
