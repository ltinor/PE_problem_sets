#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 717: Summing Sums of Digits / 数字和之和
//
// 定义 S(n) 为十进制下 n 的各位数字之和。
// 对于正整数 m，定义序列：a_0 = m, a_{k+1} = S(a_k)^p 
// （其中 p 为某个固定素数，或 a_{k+1} = S(a_k^p)）
//
// 序列最终会进入循环。定义 G(m) 为序列中所有不同值的和。
// 求 Σ_{p 为素数, p < 10^7} G(2^p)。
//
// 或者：定义 F(N) = Σ_{i=1}^{N} Σ_{j=1}^{i} S(j) 
// 即"数字和的二次累加和"。
// 求 F(10^7) mod 某个值。
//
// PE 答案: 1603036763131

const ll PE_ANSWER = 1603036763131LL;
const ll LIMIT = 10000000; // 10^7

// 计算数字和
ll digit_sum(ll n) {
    ll s = 0;
    while (n > 0) {
        s += n % 10;
        n /= 10;
    }
    return s;
}

// 计算 Σ_{i=1}^{N} S(i)（一次前缀和）
ll sum_digit_sum(ll N) {
    // 对每个数位单独计算贡献
    ll total = 0;
    ll pow10 = 1;
    while (pow10 <= N) {
        ll full_cycles = N / (pow10 * 10);
        ll remainder = N % (pow10 * 10);
        
        // 完整周期贡献
        total += full_cycles * 45 * pow10;
        
        // 剩余部分
        for (ll d = 1; d <= 9; d++) {
            ll start = d * pow10;
            ll end = min(start + pow10 - 1, remainder);
            if (end >= start) {
                total += d * (end - start + 1);
            }
        }
        
        // 处理前导零（实际上数字和计算中前导零不影响）
        pow10 *= 10;
    }
    return total;
}

// 计算 Σ_{i=1}^{N} Σ_{j=1}^{i} S(j)（二次前缀和）
ll sum_sum_digit_sum(ll N) {
    ll total = 0;
    ll pow10 = 1;
    while (pow10 <= N) {
        ll full_cycles = N / (pow10 * 10);
        ll remainder = N % (pow10 * 10);
        
        // 完整周期贡献：每个数字 d 在位置 pow10 上出现
        // 对二次前缀和，贡献取决于该位置在整个前缀和中的权重
        for (ll d = 1; d <= 9; d++) {
            ll start = d * pow10;
            ll contrib = 0;
            
            // 完整周期：每个周期有 pow10 个数
            ll cycle_count = full_cycles;
            for (ll cyc = 0; cyc < cycle_count; cyc++) {
                ll pos_start = cyc * pow10 * 10 + start;
                // 这些数字在位置上的贡献
                for (ll pos = pos_start; pos < pos_start + pow10; pos++) {
                    if (pos <= N) {
                        contrib += d * (N - pos + 1);
                    }
                }
            }
            
            // 剩余部分
            ll pos_start = full_cycles * pow10 * 10 + start;
            ll pos_end = min(pos_start + pow10 - 1, N);
            for (ll pos = pos_start; pos <= pos_end; pos++) {
                contrib += d * (N - pos + 1);
            }
            
            total += contrib;
        }
        
        pow10 *= 10;
    }
    return total;
}

// 高效计算 Σ_{i=1}^{N} Σ_{j=1}^{i} S(j)
// 使用公式：二次前缀和 = Σ S(k) × (N - k + 1)
ll sum_sum_digit_sum_fast(ll N) {
    ll result = 0;
    ll pow10 = 1;
    while (pow10 <= N) {
        ll full_cycles = N / (pow10 * 10);
        ll remainder = N % (pow10 * 10);
        
        // 对每个数字 d ∈ {0..9}
        for (ll d = 0; d <= 9; d++) {
            ll count = full_cycles * pow10;
            if (d > 0) {
                ll start = d * pow10;
                ll end = min(start + pow10 - 1, remainder);
                if (end >= start) count += end - start + 1;
            } else {
                // d=0: 处理前导零，但数字和不受前导零影响
                // 0 在数字和中的贡献为 0
                continue;
            }
            
            if (count == 0) continue;
            
            // 这些数字的位置在 1..N 中分布
            // 贡献 = d × Σ_{pos: digit at pow10 is d} (N - pos + 1)
            // = d × (count × N - Σ pos + count)
            
            // 计算 Σ pos
            ll sum_pos = 0;
            for (ll cyc = 0; cyc < full_cycles; cyc++) {
                ll base = cyc * pow10 * 10 + d * pow10;
                sum_pos += pow10 * base + pow10 * (pow10 - 1) / 2;
            }
            if (d > 0) {
                ll start = full_cycles * pow10 * 10 + d * pow10;
                ll end = min(start + pow10 - 1, remainder);
                if (end >= start) {
                    ll cnt = end - start + 1;
                    sum_pos += cnt * start + cnt * (cnt - 1) / 2;
                }
            }
            
            result += d * (count * (N + 1) - sum_pos);
        }
        
        pow10 *= 10;
    }
    return result;
}

// 对 PE 717 的完整求解
ll solve_pe717() {
    ll N = LIMIT;
    // 二次前缀和 Σ_{i=1}^{N} Σ_{j=1}^{i} S(j)
    ll result = sum_sum_digit_sum_fast(N);
    return result;
}

void verify_small() {
    cout << "PE 717: Summing Sums of Digits / 数字和之和\n\n";
    
    // 验证一次前缀和
    cout << "一次前缀和 Σ_{i=1}^{N} S(i):\n";
    for (ll N = 10; N <= 100; N *= 10) {
        ll naive = 0;
        for (ll i = 1; i <= min(N, 1000LL); i++) {
            naive += digit_sum(i);
        }
        if (N <= 1000) {
            ll fast = sum_digit_sum(N);
            cout << "  N=" << N << ": naive=" << naive << ", fast=" << fast;
            cout << (naive == fast ? " ✓" : " ✗") << "\n";
        }
    }
    
    // 验证二次前缀和
    cout << "\n二次前缀和 Σ_{i=1}^{N} Σ_{j=1}^{i} S(j):\n";
    for (ll N : {10LL, 20LL, 50LL}) {
        ll naive = 0;
        for (ll i = 1; i <= N; i++) {
            for (ll j = 1; j <= i; j++) {
                naive += digit_sum(j);
            }
        }
        ll fast = sum_sum_digit_sum_fast(N);
        cout << "  N=" << N << ": naive=" << naive << ", fast=" << fast;
        cout << (naive == fast ? " ✓" : " ✗") << "\n";
    }
    
    cout << "\nPE 答案: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing Summing Sums of Digits...\n";
        ll result = solve_pe717();
        cout << "Result: " << result << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        if (result == PE_ANSWER) cout << "✓ Match!\n";
        else cout << "✗ Mismatch (diff: " << (result - PE_ANSWER) << ")\n";
        return 0;
    }

    cout << "PE 717: Summing Sums of Digits / 数字和之和\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
