#include<bits/stdc++.h>
using namespace std;

// log factorial using lgammal (long double)
long double lfact(int x) {
    return lgammal(x + 1.0L);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;

    // P(all <= 2) = sum_{b=0}^{k/2} n! * k! / (b! * a! * (n-a-b)! * 2^b) / n^k
    // where a = k - 2b

    long double log_nk = k * logl((long double)n);
    long double log_nf = lfact(n);
    long double log_kf = lfact(k);

    // Find max log term for numerical stability
    long double max_log = -INFINITY;
    for (int b = 0; 2 * b <= k; b++) {
        int a = k - 2 * b;
        int used = a + b;
        if (used > n) continue;

        long double log_term = log_nf + log_kf
                             - lfact(b)
                             - lfact(a)
                             - lfact(n - used)
                             - b * logl(2.0L)
                             - log_nk;
        if (log_term > max_log) max_log = log_term;
    }

    // Sum with shift
    long double shifted_sum = 0.0L;
    for (int b = 0; 2 * b <= k; b++) {
        int a = k - 2 * b;
        int used = a + b;
        if (used > n) continue;

        long double log_term = log_nf + log_kf
                             - lfact(b)
                             - lfact(a)
                             - lfact(n - used)
                             - b * logl(2.0L)
                             - log_nk;

        shifted_sum += expl(log_term - max_log);
    }

    long double p_all_le2 = expl(max_log) * shifted_sum;
    long double ans = 1.0L - p_all_le2;

    if (ans < 0) ans = 0.0L;
    if (ans > 1) ans = 1.0L;

    cout << fixed << setprecision(10) << (double)ans << "\n";
    return 0;
}
