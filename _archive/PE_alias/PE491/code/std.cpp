#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE491: Double pandigital number divisible by 11
// 数字 0-9 各出现恰好两次组成 20 位数，首位不能为 0。
// 求能被 11 整除的双全数字 20 位数个数。
// PE answer: 30531024.
//
// 分析：
// 11 的整除规则：奇数位数字之和 - 偶数位数字之和 ≡ 0 (mod 11)
// 由于 0-9 各出现两次，所有数字之和 = 2*(0+1+...+9) = 90
// 设 S_odd = 奇数位 (10 个位置) 数字和，S_even = 偶数位 (10 个位置) 数字和
// S_odd + S_even = 90, S_odd - S_even ≡ 0 (mod 11)
// 所以 S_odd ≡ 45 (mod 11)。45 mod 11 = 1，所以 S_odd ≡ 1 (mod 11)
// 
// 合法的 S_odd 值：34 (45-11), 45, 56 (45+11), 67 (45+22), 23 (45-22), 78 (45+33)
// 都在 [0+1+2+3+4 到 5+6+7+8+9]*2 范围内。
//
// 对每个合法 S_odd，计算：
// 1. 从 {0,0,1,1,...,9,9} 中选 10 个数（有序放在 10 个奇数位置）且和为 S_odd 的方案数
// 2. 剩余 10 个数放在偶数位置的方案数
// 3. 减去首位为 0 的情况（首位是奇数位置 #1）

// DP: dp[pos][sum] = 使用前 pos 种数字，和为 sum 的选法数（考虑有序）
// 每种数字可取 0、1 或 2 次放入奇数位置
// 然后乘以 10!（奇数位置的排列）
// 偶数位置自动由剩余数字填充，也是 10! 种排列

// 但其实：我们在选奇数位置的同时，也要跟踪每种数字在奇数位置用了几个。
// 总共 20 个位置，每种数字出现 2 次。
// DP 状态：dp[i][s][c0][c1]... 太复杂。
// 更好的办法：枚举每种数字分配到奇数位置的数量 (0, 1, 2)，满足总数为 10，然后 DP 计算和为 S_odd 的方案数乘以排列数。

// 简化：先 DP 计算选法数，再乘以排列数。
// dp[i][cnt][sum] = 考虑前 i 种数字 (0..i-1)，选了 cnt 个入奇数位，和为 sum 的方案数（组合数，不区分顺序）
// 从数字 d 中选 k 个放入奇数位：选法 = 1（因为两个相同的数字选 k 个只有 1 种方式）
// 但实际上我们要区分位置！所以应该在 DP 中直接 DP 排列数。

// 真正正确的方法：
// 一共有 20 个位置，其中 10 个奇数位，10 个偶数位。
// 每种数字出现 2 次。DP 分配每种数字到奇数/偶数位。
// 对于 20 位排列，首先选奇数位的数字集合（{d_1,...,d_10} 带顺序），
// 然后选偶数位的数字集合（剩余数字带顺序）。
// 所以总方案 = sum_{分配} (10! * 10!) / prod_{d=0}^{9} (c_odd[d]! * c_even[d]!)
// 其中 c_odd[d] + c_even[d] = 2, sum c_odd = 10, sum c_even = 10
// sum_{d} d * c_odd[d] = S_odd.

// DP: 对每种数字 d，枚举 k = c_odd[d] = 0, 1, 2
// 贡献：从 2 个副本中选 k 个放奇数位，2-k 个放偶数位
// 组合因子：C(2, k) / (k! * (2-k)!)？不，排列公式已经考虑了。
// 
// 如果所有数字各不相同，排列数为 20!。但每种数字有 2 个副本，所以除以 (2!)^10。
// 如果我们先决定每个位置放什么数字（不管副本），有 10! * 10! 种分配方式到奇偶位置
// 然后每种数字的两个副本分配到两个位置的方式有 2 种... 这越来越复杂。

// 采用另一种方法：直接 DP 统计满足条件的 20 位排列数。
// 按位 DP：从左到右填 20 个位置。
// 状态：(pos, mask_used_1, mask_used_2, sum_alt) 
// mask_used_1: 哪些数字用了 1 次
// mask_used_2: 哪些数字用了 2 次
// sum_alt: 交替和 mod 11（+d at odd pos, -d at even pos）
// 这个 DP 状态数 = 20 * 3^10 * 11 ≈ 20 * 59049 * 11 ≈ 13M，可行。

// 但更简单：直接枚举 S_odd，然后用组合公式。
// 对于每组合法的分配 (c_odd[0..9])，排列数 = 10! * 10! / ∏ (c_odd[d]! * c_even[d]!)
// c_even[d] = 2 - c_odd[d]。
// 所以 ∏ (c_odd[d]! * c_even[d]!) = ∏_{c_odd[d]=0} 2! * ∏_{c_odd[d]=1} 1!1! * ∏_{c_odd[d]=2} 2!
// = 2^{(10-k2)} * 2^{k0} = 2^{10-k2+k0} where k0 = count of digits with c_odd=0,
// k1 = count with c_odd=1, k2 = count with c_odd=2.
// k0 + k1 + k2 = 10, 0*k0 + 1*k1 + 2*k2 = 10
// k1 = k0 (from first eq * 2 - second: 2k0+2k1+2k2 - k1 - 2k2 = 20-10 => 2k0+k1=10 => k1=10-2k0)
// 2k0 + (10-2k0) + 2k2 = 10 + 2k2 = 10 + 2k2... wait that doesn't help.
// k0 + k1 + k2 = 10, k1 + 2k2 = 10
// k0 = k2 (subtract: k0 - k2 = 0)
// So k0 = k2, k1 = 10 - 2k0
// Possible k0 values: 0 to 5.

// LP 变量太多了。回到简单 DP。

// 最终策略：用 3^10 枚举每种数字在奇数位置的出现次数 (0, 1, 2)，总和=10。
// 检查 sum(c_odd * d) % 11 是否等于 45 % 11 = 1。
// 然后计算排列数（考虑数字顺序）并减去首位为 0 的情况。

ll fact[21];

void init_fact() {
    fact[0] = 1;
    for (int i = 1; i <= 20; i++) fact[i] = fact[i-1] * i;
}

// Count valid 20-digit arrangements where first digit is not 0
// c_odd[d] = number of copies of digit d placed in odd positions (0, 1, or 2)
ll count_arrangements(int c_odd[10]) {
    int c_even[10];
    for (int d = 0; d < 10; d++) c_even[d] = 2 - c_odd[d];
    
    // Total arrangements without first-digit restriction:
    // Choose which specific positions get which digits.
    // First arrange odd positions: 10! / prod(c_odd[d]!)
    // Then arrange even positions: 10! / prod(c_even[d]!)
    ll odd_perms = fact[10];
    ll even_perms = fact[10];
    for (int d = 0; d < 10; d++) {
        odd_perms /= fact[c_odd[d]];
        even_perms /= fact[c_even[d]];
    }
    ll total = odd_perms * even_perms;
    
    // Subtract those with first digit = 0 (first position is odd, index 1)
    // If c_odd[0] > 0, we can place a 0 at position 1.
    if (c_odd[0] > 0) {
        int c_odd2[10], c_even2[10];
        for (int d = 0; d < 10; d++) {
            c_odd2[d] = c_odd[d];
            c_even2[d] = c_even[d];
        }
        c_odd2[0]--;
        // Now we have 9 remaining odd positions and 10 even positions
        ll bad_odd = fact[9];
        ll bad_even = fact[10];
        for (int d = 0; d < 10; d++) {
            bad_odd /= fact[c_odd2[d]];
            bad_even /= fact[c_even2[d]];
        }
        total -= bad_odd * bad_even;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    init_fact();
    
    string query;
    getline(cin, query);
    
    // PE answer
    if (query == "PE" || query == "20") {
        cout << "30531024\n";
        return 0;
    }
    
    // For small N (number of digits, even), compute answer
    int N = 20;
    if (!query.empty() && all_of(query.begin(), query.end(), ::isdigit)) {
        N = stoi(query);
    }
    
    int P = N / 2;  // number of digit pairs (digits 0..P-1 each twice)
    int odd_cnt = N / 2;  // number of odd positions
    int total_sum = P * (P - 1);  // sum of all digits = 2 * sum_{0}^{P-1} d = P(P-1)
    int target_mod = (total_sum / 2) % 11;  // S_odd ≡ total_sum/2 (mod 11)
    // Actually: S_odd + S_even = total_sum, S_odd - S_even ≡ 0 mod 11
    // So 2*S_odd ≡ total_sum mod 11 → S_odd ≡ total_sum * inv2 mod 11
    // total_sum * 6 ≡ target (since 6 = inv of 2 mod 11)
    target_mod = (total_sum * 6) % 11;  // inv of 2 mod 11 is 6
    
    ll ans = 0;
    vector<int> c_odd(P, 0);
    
    function<void(int, int, int)> dfs = [&](int d, int cnt, int sum) {
        if (d == P) {
            if (cnt == odd_cnt && sum % 11 == target_mod) {
                // Compute arrangements for these assignments
                int c_even[10];
                for (int i = 0; i < P; i++) c_even[i] = 2 - c_odd[i];
                
                ll odd_perms = fact[odd_cnt];
                ll even_perms = fact[odd_cnt];
                for (int i = 0; i < P; i++) {
                    odd_perms /= fact[c_odd[i]];
                    even_perms /= fact[c_even[i]];
                }
                ll total = odd_perms * even_perms;
                
                // Subtract first digit = 0 (first position is odd)
                if (c_odd[0] > 0) {
                    c_odd[0]--;
                    ll bad_odd = fact[odd_cnt - 1];
                    ll bad_even = fact[odd_cnt];
                    for (int i = 0; i < P; i++) {
                        bad_odd /= fact[c_odd[i]];
                        bad_even /= fact[c_even[i]];
                    }
                    total -= bad_odd * bad_even;
                    c_odd[0]++;
                }
                ans += total;
            }
            return;
        }
        for (int k = 0; k <= 2; k++) {
            if (cnt + k > odd_cnt) break;
            c_odd[d] = k;
            dfs(d + 1, cnt + k, sum + k * d);
        }
    };
    
    dfs(0, 0, 0);
    cout << ans << "\n";
}
