#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// PE396（缩数据简单版）：弱古德斯坦序列
// g1 = n；gk = 将 g_{k-1} 写成 k 进制后视作 k+1 进制数，再减 1。
// G(n) 为序列中非零元素个数，求 Σ_{n=1}^{N-1} G(n)。
// 缩小参数：直接模拟即可（原题 N<16 需要 Ackermann 级增长分析，这里限制 N≤8）。

// 将 num 按 base 进制拆位，再按 base+1 进制重新解释
ll reinterpret(ll num, ll base) {
    ll result = 0, p = 1;
    while (num) {
        result += (num % base) * p;
        num /= base;
        p *= (base + 1);
    }
    return result;
}

// 返回 G(n)：第 n 个弱古德斯坦序列中非零元素个数
ll goodstein_length(ll n) {
    ll cnt = 0, g = n, k = 2;
    while (g > 0) {
        cnt++;
        g = reinterpret(g, k) - 1;
        k++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    // 缩数据：弱 Goodstein 序列 Ackermann 级增长，N≤8 可快速模拟，N>8 超时
    if (N > 9) {
        cout << "N 超出缩数据范围（需 N ≤ 8）\n";
        return 0;
    }
    ll total = 0;
    for (ll n = 1; n < N; n++) total += goodstein_length(n);
    cout << total << "\n";
}
