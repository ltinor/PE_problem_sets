#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 943: Self Describing Sequences / 自描述数列（简单版本）
//
// 原题：Σ T(a,b, 22332223332233) 对所有 2<=a,b<=223, a!=b，模 2233222333。
// 改编：读入 a b N，输出 T(a,b,N)（前 N 个元素之和）。
//
// 自描述数列生成（广义 Kolakoski）：
//   第一个 run 由 a 组成，长度为 a（即 seq[0..a-1] = a）。
//   之后每个 run 的长度 = seq[read]（从 read=1 开始），符号 a、b 交替。
//
// 验证点：T(2,3,10)=25, T(4,2,10^4)=30004, T(5,8,10^6)=6499871。

ll solve(int a, int b, ll N) {
    if (N <= 0) return 0;
    vector<int> seq;
    seq.reserve((size_t)min(N, (ll)20000000));
    // 第一个 run：a 个 a
    for (int i = 0; i < a && (ll)seq.size() < N; i++) seq.push_back(a);
    int read = 1;
    int symbol = b; // 第二个 run 的符号
    while ((ll)seq.size() < N) {
        int run_len = seq[read];
        for (int j = 0; j < run_len && (ll)seq.size() < N; j++)
            seq.push_back(symbol);
        symbol = (symbol == a ? b : a);
        read++;
    }
    ll sum = 0;
    for (ll i = 0; i < N; i++) sum += seq[i];
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int a, b;
    ll N;
    if (!(cin >> a >> b >> N)) return 0;
    if (a <= 0 || b <= 0 || a == b || N < 1 || N > 10000000) return 0;
    cout << solve(a, b, N) << "\n";
    return 0;
}
