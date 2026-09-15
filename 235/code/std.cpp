#include<bits/stdc++.h>
using namespace std;
typedef long double ld;

// PE 235: Arithmetic Geometric sequence
// s(n) = Σ_{k=1}^{n} (900 - 3k) * r^{k-1}
// Find r such that s(n) = target S.
// PE answer: 1.002322108633 for n=5000, S=-600000000000

// Closed form: s(r) = A*(1-r^n)/(1-r) + D*r*(1-n*r^{n-1}+(n-1)*r^n)/(1-r)^2
// where A = 897, D = -3

ld compute_s(ld r, int n) {
    if (fabsl(r - 1.0L) < 1e-15L) {
        // s(1) = Σ (900-3k) = 900n - 3n(n+1)/2
        return 900.0L * n - 1.5L * n * (n + 1);
    }

    // 溢出检测：Apple Silicon 上 long double == double（8 字节，LDBL_MAX≈1.8e308）。
    // r^n 溢出当 n*log(r) 超过 log(LDBL_MAX)≈709。
    // 此时 s(r) 主导项 (900-3n)*r^{n-1} 是巨大负数，远小于 target，
    // 返回一个足够负的哨兵值即可（不影响二分单调性判断）。
    if (r > 1.0L) {
        long double logrn = (long double)n * logl(r);
        if (logrn > logl(LDBL_MAX) - 10.0L) {
            return -1.0e300L;
        }
    }

    ld A = 897.0L;
    ld D = -3.0L;

    ld rn = powl(r, n);
    ld rn1 = powl(r, n - 1);

    ld term1 = A * (1.0L - rn) / (1.0L - r);
    ld term2 = D * r * (1.0L - n * rn1 + (n - 1) * rn) / ((1.0L - r) * (1.0L - r));

    return term1 + term2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ld target;
    cin >> n >> target;

    // s(r) decreases as r increases for r > 1
    // s(1) = 900n - 3n(n+1)/2
    ld s1 = 900.0L * n - 1.5L * n * (n + 1);

    if (fabsl(target - s1) < 1e-12L) {
        cout << fixed << setprecision(12) << 1.0L << "\n";
        return 0;
    }

    ld lo, hi;

    if (target < s1) {
        // r > 1
        lo = 1.0L;
        hi = 2.0L;
        // Expand hi until s(hi) < target
        while (compute_s(hi, n) > target) {
            hi *= 1.5L;
        }
    } else {
        // r < 1
        lo = 0.0L;
        hi = 1.0L;
        // s(0) = 897
    }

    // Binary search
    for (int iter = 0; iter < 100; iter++) {
        ld mid = (lo + hi) / 2.0L;
        ld smid = compute_s(mid, n);

        if (target < s1) {
            // s decreasing in r: s(mid) < target → mid too big
            if (smid < target) {
                hi = mid;
            } else {
                lo = mid;
            }
        } else {
            // s increasing in r: s(mid) < target → mid too small
            if (smid < target) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
    }

    cout << fixed << setprecision(12) << (lo + hi) / 2.0L << "\n";
    return 0;
}
