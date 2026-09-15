#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 942（简单版本）：梅森平方根 Mersenne's Square Root
//
// 原题：p = 2^q - 1 对 q = 74207281 是天文数字，需 O(q) 次 Mersenne 归约平方。
// 简单版本：缩数据到 q <= 62（p = 2^q-1 可装入 128 位），仍用同一条
//           O(log) 快速算法求最小平方根，几秒内算出。
//
// R(q) = 最小的正整数 x 使 x^2 ≡ q (mod p)，其中 p = 2^q - 1。
// 验证点：R(5)=6，R(17)=47569。
//
// 算法：p = 2^q - 1 对 q>=2 恒有 p ≡ 3 (mod 4)，故可用欧拉判别：
//   x = q^((p+1)/4) mod p，其中 (p+1)/4 = 2^{q-2}，
//   即对 q 连续平方 (q-2) 次。若 x^2 ≡ q 则 R = min(x, p-x)；
//   否则（q 非二次剩余 / p 为合数）退回线性搜索，无解输出 -1。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll q;
    if (!(cin >> q)) return 0;

    i128 p = ((i128)1 << q) - 1;  // 2^q - 1

    auto linear = [&]() -> ll {
        for (i128 x = 1; x < p; x++)
            if (x * x % p == q % p) return (ll)x;
        return -1;
    };

    if (q == 1) {
        cout << 1 << "\n";  // mod 1 恒成立
        return 0;
    }
    if (q < 3) {
        cout << linear() << "\n";
        return 0;
    }

    // x = q^(2^(q-2)) mod p，即连续平方 q-2 次
    i128 x = q % p;
    for (ll i = 0; i < q - 2; i++) x = x * x % p;

    if (x * x % p == q % p) {
        i128 other = p - x;
        cout << (ll)(x < other ? x : other) << "\n";
    } else {
        cout << linear() << "\n";
    }
    return 0;
}
