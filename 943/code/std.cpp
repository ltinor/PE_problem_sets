#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 943（简单版本）：自描述数列 Self Describing Sequences
//
// 原题：N = 22332223332233 ≈ 2.2e13，且要对 ~5 万组 (a,b) 求和，需要
//       O(log N) 的分形/生成函数加速。
// 简单版本：缩数据到 N <= 1e6，直接用定义逐段生成数列，O(N) 即可，秒出。
//
// 数列由 a、b 交替的连续段组成，首元素为 a，且「每段长度组成的数列」就是
// 原数列本身。因此每段的长度只能是 a 或 b。
// T(a,b,N) = 前 N 项之和。
//
// 验证点：T(2,3,10)=25，T(4,2,10^4)=30004，T(5,8,10^6)=6499871。
//
// 生成算法（要求 a>=2，与原题 2<=a,b<=223 一致）：
//   seq[0..a-1] = a（第 0 段：a 个 a）
//   读指针 j=1；只要长度 < N：
//       把 seq[j] 个「(j 为偶 ? a : b)」追加到末尾，然后 j++。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b, N;
    if (!(cin >> a >> b >> N)) return 0;

    vector<int> seq;
    seq.reserve(N);
    for (int i = 0; i < a; i++) seq.push_back((int)a);

    int j = 1;
    while ((ll)seq.size() < N) {
        int run_len = seq[j];
        int sym = (j % 2 == 0) ? (int)a : (int)b;
        for (int t = 0; t < run_len; t++) seq.push_back(sym);
        j++;
    }

    ll sum = 0;
    for (ll i = 0; i < N; i++) sum += seq[i];
    cout << sum << "\n";
    return 0;
}
