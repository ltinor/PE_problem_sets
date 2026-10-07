// PE369: Badugi Poker
// f(n) = 从 52 张牌中取 n 张、包含 4 张"百得之"(4 点数互异 + 4 花色互异)的取法数.
// 无 Badugi <=> 点数-花色二部图最大匹配 <= 3 (Konig). 用 16 个花色子集的最大匹配状压 DP 精确计算.
// 验证: f(5) = 514800 (题面给定), sum f(4..13) = 862400558448 (官方答案).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    // 13 轮 DP: 状态 = M[0..15] (16 个花色子集的最大匹配数), 计数按已取张数 n
    map<pair<array<int,16>,int>, ll> dp;
    array<int,16> start{}; start.fill(0);
    dp[{start, 0}] = 1;
    for (int rank = 0; rank < 13; rank++) {
        map<pair<array<int,16>,int>, ll> ndp;
        for (auto& [kv, c] : dp) {
            auto st = kv.first; int n = kv.second;
            for (int T = 0; T < 16; T++) {
                int nn = n + __builtin_popcount(T);
                if (nn > 13) continue;
                array<int,16> nm;
                for (int S = 0; S < 16; S++) {
                    int best = st[S];
                    for (int s = 0; s < 4; s++)
                        if ((T >> s & 1) && (S >> s & 1))
                            best = max(best, st[S ^ (1 << s)] + 1);
                    nm[S] = best;
                }
                ndp[{nm, nn}] += c;
            }
        }
        dp = move(ndp);
    }
    vector<ll> f(14, 0);
    for (auto& [kv, c] : dp) if (kv.first[15] == 4) f[kv.second] += c;

    string first; cin >> first;
    if (first == "PE") {
        ll sum = 0;
        for (int n = 4; n <= 13; n++) sum += f[n];
        cout << sum << "\n";
        return 0;
    }
    int n = stoi(first);
    if (n < 4 || n > 13) { cout << "0\n"; return 0; }
    cout << f[n] << "\n";
}
