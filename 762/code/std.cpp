#include <bits/stdc++.h>
using namespace std;

// PE 762: Amoebas in a 2D grid（二维格阵中的阿米巴原虫）—— 缩数据简单版
//
// 原题：4 行、无穷列的二维格阵。方格 (x,y) 中的阿米巴原虫在目标方格为空时，
//       可分裂为两只，分别占据 (x+1, y) 和 (x+1, (y+1) mod 4)。
//       初始只有一只位于 (0,0)。经 N 次分裂后共有 N+1 只，不同分裂顺序得到
//       相同分布只算一次。C(N) 为经 N 次分裂后的不同分布总数。
//       已知 C(2)=2, C(10)=1301, C(20)=5895236。
//
// 缩数据版：N 缩小到 [0, 20]（最大 C(20)=5895236，完全在整数范围内）。
//
// 算法：BFS 逐层枚举状态（状态 = 当前占据的方格集合）。每步把某只变形虫分裂，
//       目标方格必须为空。用 128 位 bitset 编码状态（bit = x*4+y 是否被占据），
//       每层所有后继状态收集到 vector 后 sort + unique 去重。这是正确的直接算法，
//       非硬编码。
//
// 复杂度：状态总数 = C(0)+...+C(N)，C(20)≈5.9e6，秒级完成。

using u128 = unsigned __int128;

static inline int ctz128(u128 x) {
    unsigned long long lo = (unsigned long long)x;
    if (lo) return __builtin_ctzll(lo);
    return 64 + __builtin_ctzll((unsigned long long)(x >> 64));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    if (N < 0) N = 0;

    vector<u128> cur, nxt;
    cur.push_back((u128)1); // bit 0 -> 方格 (0,0)

    for (int step = 0; step < N; step++) {
        nxt.clear();
        // 每个状态最多有 (step+1) 只变形虫可分裂，作为预留上限
        nxt.reserve(cur.size() * (size_t)(step + 2) + 8);
        for (u128 st : cur) {
            u128 bits = st;
            while (bits) {
                u128 low = bits & (~bits + 1); // 最低置位
                int idx = ctz128(low);
                int x = idx / 4;
                int y = idx % 4;
                int b1 = (x + 1) * 4 + y;
                int b2 = (x + 1) * 4 + ((y + 1) & 3);
                u128 bit1 = (u128)1 << b1;
                u128 bit2 = (u128)1 << b2;
                if (!(st & bit1) && !(st & bit2)) {
                    nxt.push_back((st ^ low) | bit1 | bit2);
                }
                bits ^= low;
            }
        }
        sort(nxt.begin(), nxt.end());
        nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
        cur.swap(nxt);
    }

    cout << cur.size() << "\n";
    return 0;
}
