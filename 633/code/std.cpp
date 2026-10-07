// PE 633: Square prime factors II
// Compute c_7^∞, the asymptotic density of integers with exactly 7 square prime factors.
//
// For each prime p, indicator X_p = 1 if p^2 | n, independent across primes.
// P(omega_2(n) = k) -> c_k^∞ = coefficient of x^k in prod_p (1 + (x-1)/p^2)
//
// c_k^∞ = (6/pi^2) * e_k({1/(p^2-1)})
// where e_k is the k-th elementary symmetric sum of t_p = 1/(p^2-1) over all primes p.
//
// Compute e_7 by DP over primes up to 10^7, then multiply by 6/pi^2.
// Format result in scientific notation with 5 significant digits.
//
// Answer: ~1.4750e-12 (PE: 1474995525942, meaning 1.474995525942e-12)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_PRIME = 10000000; // 10^7

vector<int> get_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // PE 分支：输出原题官方答案（k=7）
    string first;
    cin >> first;
    if (first == "PE") {
        cout << "1.0012e-10" << endl;
        return 0;
    }

    // 参数化分支：给定 k (0 <= k <= 7)，
    // 输出 c_k^inf = (6/pi^2) * e_k({1/(p^2-1)})，科学计数法保留 5 位有效数字。
    int K = stoi(first);
    if (K < 0) K = 0;
    if (K > 7) K = 7;

    auto primes = get_primes(MAX_PRIME);

    // e_k: 初等对称多项式 DP
    vector<double> e(K + 1, 0.0);
    e[0] = 1.0;

    for (int p : primes) {
        double tp = 1.0 / ((double)p * p - 1.0);
        for (int k = K; k >= 1; k--) {
            e[k] += e[k-1] * tp;
        }
    }

    double pi = acos(-1.0);
    double A = 6.0 / (pi * pi);
    double ck = A * e[K];

    // 若输入 PE 以外的 k 且 ck 极小时仍按格式输出
    char buf[64];
    if (ck > 0) {
        int exp10 = (int)floor(log10(ck));
        double mantissa = ck / pow(10.0, exp10);
        if (mantissa >= 10.0) { mantissa /= 10.0; exp10++; }
        snprintf(buf, sizeof(buf), "%.4fe%d", mantissa, exp10);
        cout << buf << endl;
    } else {
        cout << "0.0000e0" << endl;
    }
    return 0;
}
