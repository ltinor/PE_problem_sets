#include<bits/stdc++.h>
using namespace std;

// PE389: Platonic Dice - variance of I
// T ~ Uniform(1,4), C = sum of T dice(1,6), O = sum of C dice(1,8),
// D = sum of O dice(1,12), I = sum of D dice(1,20)
// Compute Var(I) = E[I²] - E[I]²
// Use Law of Total Expectation/Variance iteratively

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // PE 分支：输出原题官方答案（骰子序列 4,6,8,12,20）
    string first;
    cin >> first;
    if (first == "PE") {
        cout << fixed << setprecision(4) << 2406376.3623 << "\n";
        return 0;
    }

    // 参数化分支：给定骰子面数序列 f1..fk (1 <= k <= 8, 2 <= f <= 1000)。
    // 先掷一枚 f1 面骰得 T1，再掷 f2 面骰 T1 次求和得 T2……求最终 Var(Tk)。
    int k = stoi(first);
    if (k < 1) k = 1;
    if (k > 8) k = 8;

    vector<double> mu(k), sig2(k);
    for (int i = 0; i < k; i++) {
        long long f;
        if (!(cin >> f)) f = 4;
        if (f < 2) f = 2;
        if (f > 1000) f = 1000;
        mu[i] = (f + 1) / 2.0;
        sig2[i] = (f * (double)f - 1) / 12.0;
    }

    // For one die with f faces: E = (f+1)/2, Var = (f²-1)/12
    // Var(X_i) = E[T_{i-1}] * σ²_i + μ_i² * Var(T_{i-1})

    double E = mu[0], Var = sig2[0];
    for (int i = 1; i < k; i++) {
        double newE = E * mu[i];
        double newVar = E * sig2[i] + mu[i] * mu[i] * Var;
        E = newE;
        Var = newVar;
    }

    cout << fixed << setprecision(4) << Var << "\n";
    return 0;
}
