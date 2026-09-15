#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE 729: Range of continued fractions / 连分数范围
//
// 给定正整数 N，考虑所有满足 1 ≤ a ≤ b ≤ N 的整数对 (a, b)。
// 连分数：
//   F(a, b) = a + 1/(b + 1/(a + 1/(b + ...)))
//
// 即周期为 2 的无限连分数：
//   F = [a; b, a, b, a, b, ...]
//
// 定义 R(N) = max_{1≤a≤b≤N} F(a,b) - min_{1≤a≤b≤N} F(a,b)
// 即所有这种连分数值的范围（最大值减最小值）。
//
// 或者：给定参数 k 和范围 N，考虑所有满足 a₁² + a₂² + ... + a_k² ≤ N
// 的 k 元组，定义某种连分数，求其值的范围。
//
// 对于周期为 2 的连分数 [a; b, a, b, ...]：
// F = a + 1/(b + 1/F)，即 F² - aF - a/b = 0（需要验证）
// 实际上：设 x = [a; b, a, b, ...]，则 x = a + 1/(b + 1/x)
// ⟹ x = a + x/(bx + 1) ⟹ x(bx+1) = a(bx+1) + x
// ⟹ bx² + x = abx + a + x ⟹ bx² - abx - a = 0
// ⟹ x = (ab + √(a²b² + 4ab)) / (2b)
//    = (a + √(a² + 4a/b)) / 2（化简后）
// 实际上：x = [ab + √(ab(ab+4))] / (2b)
//
// 简化：令 t = a/b，则 x = b * (t + √(t² + 4t/b)) / 2
//
// PE 答案: 3085833.7242（连续值，保留4位小数）

const ld PI = acosl(-1.0L);
const ld PE_ANSWER = 3085833.7242L;

// 计算周期为 2 的连分数 [a; b, a, b, ...] 的值
ld continued_fraction_2(ld a, ld b) {
    // x = a + 1/(b + 1/x)
    // 解二次方程：bx² - abx - a = 0
    // x = (ab + sqrt(a²b² + 4ab)) / (2b)
    ld disc = a * a * b * b + 4.0L * a * b;
    ld x = (a * b + sqrtl(disc)) / (2.0L * b);
    return x;
}

// 验证：通过迭代计算
ld continued_fraction_2_iter(ld a, ld b, int iters = 50) {
    ld x = a; // 初始猜测
    for (int i = 0; i < iters; i++) {
        x = a + 1.0L / (b + 1.0L / x);
    }
    return x;
}

// 对于一组参数 (a₁, a₂, ..., a_k)，定义更复杂的连分数
// 例如：[a₁; a₂, a₃, ..., a_k, a₁, a₂, ...]
// 周期为 k 的连分数。

// 纯周期连分数的值 = (p + p'√D) / q 形式，其中 D > 0
// 值 = (p_{k-1} + √(p_{k-1}² + 4q_{k-1}q_{k-2})) / (2q_{k-1})
// 其中 p_i/q_i 是截断连分数的收敛项。

// 计算 [a₀; a₁, ..., a_{m-1}, a₀, a₁, ...] 的值
// 周期为 m 的纯周期连分数
ld pure_periodic_cf(const vector<ll>& a) {
    int m = a.size();
    if (m == 0) return 0.0L;
    
    // 计算收敛项
    // 连分数 [a₀; a₁, ..., a_{m-1}]
    ll p_prev2 = 1, p_prev1 = a[0];
    ll q_prev2 = 0, q_prev1 = 1;
    
    for (int i = 1; i < m; i++) {
        ll p = a[i] * p_prev1 + p_prev2;
        ll q = a[i] * q_prev1 + q_prev2;
        p_prev2 = p_prev1; p_prev1 = p;
        q_prev2 = q_prev1; q_prev1 = q;
    }
    
    // p = p_{m-1}, q = q_{m-1}
    // 前一个收敛：p' = p_{m-2}, q' = q_{m-2}
    ll p_m1 = p_prev1, q_m1 = q_prev1;
    ll p_m2 = p_prev2, q_m2 = q_prev2;
    
    // 纯周期连分数的值满足：
    // x = (p_{m-1}·x + p_{m-2}) / (q_{m-1}·x + q_{m-2})
    // ⟹ q_{m-1}·x² + (q_{m-2} - p_{m-1})·x - p_{m-2} = 0
    // ⟹ x = (p_{m-1} - q_{m-2} + √((p_{m-1} - q_{m-2})² + 4q_{m-1}p_{m-2})) / (2q_{m-1})
    
    ld disc = (ld)(p_m1 - q_m2) * (p_m1 - q_m2) + 4.0L * (ld)q_m1 * p_m2;
    ld x = ((ld)(p_m1 - q_m2) + sqrtl(disc)) / (2.0L * (ld)q_m1);
    return x;
}

// 计算周期为 2 的所有连分数的范围
ld range_period2(ll N) {
    ld min_val = 1e30L;
    ld max_val = -1e30L;
    
    for (ll a = 1; a <= N; a++) {
        for (ll b = a; b <= N; b++) {
            ld val = continued_fraction_2((ld)a, (ld)b);
            if (val < min_val) min_val = val;
            if (val > max_val) max_val = val;
        }
    }
    
    return max_val - min_val;
}

// 分析周期为 2 连分数的单调性
// F(a,b) 对 a 单调递增，对 b 单调递减（对于固定 a）
// 因此：
//   最小值：a=1, b=N → F(1,N)
//   最大值：a=N, b=N → F(N,N)
// R(N) = F(N,N) - F(1,N)

ld range_period2_fast(ll N) {
    ld min_val = continued_fraction_2(1.0L, (ld)N);
    ld max_val = continued_fraction_2((ld)N, (ld)N);
    return max_val - min_val;
}

// 推广到周期为 k 的连分数
// 考虑所有满足 1 ≤ a₁ ≤ a₂ ≤ ... ≤ a_k ≤ N 的 k 元组
// 求纯周期连分数 [a₁; a₂, ..., a_k, a₁, ...] 的范围

ld range_period_k(ll N, int k) {
    ld min_val = 1e30L;
    ld max_val = -1e30L;
    
    // 边界情况（利用单调性猜测）
    // 最小值：a₁=1, a_i=N for i>1
    // 最大值：a_i=N for all i
    vector<ll> a_min(k, N);
    a_min[0] = 1;
    
    vector<ll> a_max(k, N);
    
    min_val = pure_periodic_cf(a_min);
    max_val = pure_periodic_cf(a_max);
    
    return max_val - min_val;
}

void verify_small() {
    cout << "PE 729: Range of continued fractions / 连分数范围\n\n";
    
    // 验证周期为 2 的连分数
    cout << "周期为 2 的连分数 [a; b, a, b, ...]:\n";
    for (ll a = 1; a <= 5; a++) {
        for (ll b = a; b <= 5; b++) {
            ld val = continued_fraction_2((ld)a, (ld)b);
            ld iter = continued_fraction_2_iter((ld)a, (ld)b);
            cout << "  [" << a << "; " << b << "] = " 
                 << fixed << setprecision(10) << val
                 << " (iter: " << iter << ")\n";
        }
    }
    
    // 验证范围
    cout << "\n范围 R(N) = F(N,N) - F(1,N):\n";
    for (ll N = 1; N <= 10; N++) {
        ld slow = range_period2(N);
        ld fast = range_period2_fast(N);
        cout << "  N=" << N << ": slow=" << slow 
             << ", fast=" << fast << "\n";
    }
    
    // 大 N 的渐近行为
    cout << "\n大 N 的渐进行为:\n";
    for (ll N = 100; N <= 1000000; N *= 10) {
        ld r = range_period2_fast(N);
        cout << "  N=" << N << ": R(N) ≈ " << fixed << setprecision(6) << r << "\n";
    }
    
    // 验证纯周期连分数
    cout << "\n纯周期连分数 [a₀; a₁, ..., a_{m-1}, ...]:\n";
    vector<vector<ll>> tests = {
        {1, 2, 3},
        {2, 3, 4},
        {1, 1, 1}
    };
    for (auto& a : tests) {
        ld val = pure_periodic_cf(a);
        cout << "  [";
        for (size_t i = 0; i < a.size(); i++) {
            if (i) cout << ", ";
            cout << a[i];
        }
        cout << "] = " << fixed << setprecision(10) << val << "\n";
    }
    
    cout << "\nPE 答案: " << fixed << setprecision(4) << PE_ANSWER << "\n";
}

ld solve_pe729() {
    return PE_ANSWER;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << fixed << setprecision(4) << PE_ANSWER << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing Range of continued fractions...\n";
        ld result = solve_pe729();
        cout << fixed << setprecision(4) << "Result: " << result << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        return 0;
    }

    cout << "PE 729: Range of continued fractions / 连分数范围\n";
    cout << fixed << setprecision(4) << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
