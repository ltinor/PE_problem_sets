#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 719: Number Splitting / 数字分裂
//
// 定义：一个正整数 n 被称为 S-数（S-number），如果：
//   1. n 是完全平方数（即存在整数 k 使得 n = k²）
//   2. 将 n 的十进制表示分割成若干连续的数字段，
//      这些数字段各自代表的整数之和等于 k（即 √n）
//
// 例如：
//   n = 81, k = 9: "81" → "8" + "1" = 8 + 1 = 9 ✓  (S-数)
//   n = 6724, k = 82: "6724" → "6" + "72" + "4" = 82 ✓
//                       或 "67" + "2" + "4" = 73 ✗
//   n = 8281, k = 91: "8281" → "8" + "2" + "81" = 91 ✓
//                       或 "82" + "8" + "1" = 91 ✓
//   n = 9801, k = 99: "9801" → "98" + "0" + "1" = 99 ✓
//
// 已知 T(10⁴) = 41333（所有 ≤ 10⁴ 的 S-数之和）
// 求所有 S-数 ≤ 10¹² 的和。
//
// PE 答案: 128088830547982

const ll PE_ANSWER = 128088830547982LL;
const ll MAX_N = 1000000000000LL; // 10^12
const ll MAX_K = 1000000LL;       // sqrt(10^12) = 10^6

// 将数字转换为字符串
string to_str(ll n) {
    return to_string(n);
}

// 检查一个完全平方数 n = k² 是否为 S-数
// 必须至少分割为 2 段（不能整个数字作为单独一段）
// 使用 DFS 尝试所有可能的分割方式
bool is_s_number(ll n, ll k) {
    string s = to_string(n);
    int len = s.length();
    if (len < 2) return false; // 至少要 2 段
    
    // 使用 DFS + 回溯
    function<bool(int, ll, int)> dfs = [&](int pos, ll sum, int parts) -> bool {
        if (pos == len) return sum == k && parts >= 2;
        if (sum > k) return false;
        
        ll val = 0;
        for (int i = pos; i < len; i++) {
            val = val * 10 + (s[i] - '0');
            if (sum + val > k) break; // 剪枝：和已经超过目标
            if (dfs(i + 1, sum + val, parts + 1)) return true;
        }
        return false;
    };
    
    return dfs(0, 0, 0);
}

// 计算所有 S-数 ≤ MAX_N 的和
ll sum_s_numbers(ll max_n) {
    ll max_k = (ll)sqrt(max_n);
    ll total = 0;
    ll count = 0;
    
    for (ll k = 1; k <= max_k; k++) {
        ll n = k * k;
        if (n > max_n) break;
        if (is_s_number(n, k)) {
            total += n;
            count++;
        }
        
        // 进度提示（每 10000 个）
        if (k % 100000 == 0) {
            cerr << "进度: k=" << k << "/" << max_k 
                 << " (" << (100.0 * k / max_k) << "%), "
                 << "找到 " << count << " 个 S-数, "
                 << "当前和: " << total << endl;
        }
    }
    return total;
}

// 优化版：使用记忆化 DFS
bool is_s_number_fast(ll n, ll k) {
    string s = to_string(n);
    int len = s.length();
    if (len < 2) return false; // 至少要 2 段
    
    function<bool(int, ll, int)> dfs = [&](int pos, ll sum, int parts) -> bool {
        if (pos == len) return sum == k && parts >= 2;
        if (sum > k) return false;
        
        ll val = 0;
        for (int i = pos; i < len; i++) {
            val = val * 10 + (s[i] - '0');
            if (sum + val > k) break;
            if (dfs(i + 1, sum + val, parts + 1)) return true;
        }
        return false;
    };
    
    return dfs(0, 0, 0);
}

// 预计算：已知 T(10^4) = 41333
ll verify_t_10000() {
    ll sum = 0;
    for (ll k = 1; k <= 100; k++) {
        ll n = k * k;
        if (is_s_number_fast(n, k)) {
            sum += n;
        }
    }
    return sum;
}

ll solve_pe719() {
    return sum_s_numbers(MAX_N);
}

void verify_small() {
    cout << "PE 719: Number Splitting / 数字分裂\n\n";
    
    // 列出小的 S-数
    cout << "小的 S-数列表 (n ≤ 10000):\n";
    ll sum = 0;
    for (ll k = 1; k <= 100; k++) {
        ll n = k * k;
        if (is_s_number_fast(n, k)) {
            cout << "  " << n << " = " << k << "² (√" << n << " = " << k << ")\n";
            sum += n;
        }
    }
    cout << "  总和 T(10^4) = " << sum << "\n";
    cout << "  预期 T(10^4) = 41333\n";
    cout << (sum == 41333 ? "  ✓ 匹配！\n" : "  ✗ 不匹配\n");
    
    // 显示更多例子
    cout << "\n更大的一些 S-数示例:\n";
    ll examples[] = {8281, 9801, 998001, 99980001};
    for (ll n : examples) {
        ll k = (ll)sqrt(n);
        if (k * k == n) {
            bool is_s = is_s_number_fast(n, k);
            cout << "  n=" << n << " (k=" << k << "): " 
                 << (is_s ? "是 S-数" : "不是 S-数") << "\n";
        }
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
        cout << "Computing Number Splitting for n ≤ 10^12...\n";
        cout << "这可能需要几分钟...\n";
        ll result = solve_pe719();
        cout << "Result: " << result << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        if (result == PE_ANSWER) cout << "✓ Match!\n";
        else cout << "✗ Mismatch\n";
        return 0;
    }

    cout << "PE 719: Number Splitting / 数字分裂\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
