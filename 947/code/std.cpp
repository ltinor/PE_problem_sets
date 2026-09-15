#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 947: Fibonacci Residues / 斐波那契余数（缩数据简单版）
//
// (a,b,m)-数列：g(0)=a, g(1)=b, g(n) = (g(n-1)+g(n-2)) mod m。
// p(a,b,m) 为其周期。s(m) = Σ_{a=0}^{m-1} Σ_{b=0}^{m-1} p(a,b,m)^2，
// S(M) = Σ_{m=1}^{M} s(m)。
//
// 原题求 S(10^6) mod 999999893。缩数据版：读入 M (1 <= M <= 1000)，
// 输出 S(M) mod 999999893。
//
// 算法：状态转移 T(a,b) = (b, (a+b) mod m)。T 是 (Z/mZ)^2 上的
// 双射（矩阵 [[0,1],[1,1]]，行列式 = -1），因此每个 (a,b) 恰好
// 位于一个环上，p(a,b,m) 就是该环的长度。枚举所有环即可，复杂度
// O(m^2) per m，总复杂度 O(M^3)。
//
// 验证点：s(3)=513, s(10)=225820, S(3)=542, S(10)=310897。

const ll MOD = 999999893LL;
const int MAX_M = 1000;

// s(m) = Σ_{(a,b)} p^2 = Σ_{环} (环长)^3
ll s_of_m(int m) {
    long long total = (long long)m * m;
    vector<int> period(total, 0);
    vector<int> buf(total); // 环状态缓冲，复用避免反复分配
    ll s = 0;
    for (int a = 0; a < m; a++) {
        for (int b = 0; b < m; b++) {
            int start = a * m + b;
            if (period[start]) continue;
            int x = a, y = b, len = 0;
            do {
                buf[len++] = x * m + y;
                int nx = y;
                int ny = (x + y) % m;
                x = nx; y = ny;
            } while (!(x == a && y == b));
            for (int i = 0; i < len; i++) period[buf[i]] = len;
            s = (s + (i128)len * len * len) % MOD;
        }
    }
    return s;
}

ll solve(int M) {
    ll ans = 0;
    for (int m = 1; m <= M; m++) {
        ans = (ans + s_of_m(m)) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int M;
    if (!(cin >> M)) return 0;
    if (M < 1 || M > MAX_M) return 0;
    cout << solve(M) << "\n";
    return 0;
}
