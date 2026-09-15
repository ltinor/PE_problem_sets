#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 963: Removing Trits / 移除三进制位  (简单版本 / simple version)
//
// 原题：求 F(10^5)。博弈 + 高维计数，需要深刻的组合博弈分析（与 PE 882 "Removing Bits" 相关）。
// 简单版本：缩小数据范围，读入 N，直接用「记忆化搜索 + 极小极大」在四元组局面空间上精确求解 F(N)。
//
// 规则回顾：
//   两位玩家各持一张纸，各写有两个正整数。轮到某位玩家时，可执行：
//     - 从「自己」纸上的一个数中删除一个 0（三进制位）；
//     - 从「对手」纸上的一个数中删除一个 1；
//     - 从「任意」纸上的一个数中删除一个 2。
//   删除后不得出现前导零；删除最后一位会使该数变为 0（0 是终态，无法再移动）。无法行动者输。
//   "公平" = 无论谁先手都必败（即先手必败的局面）。
//   F(N) = 所有数均不超过 N 的公平初始局面个数。验证点：F(5) = 21。
//
// 算法（精确、无硬编码）：
//   局面用一个五元组 (a,b,c,d,side) 表示：(a,b) 是玩家 1 的纸，(c,d) 是玩家 2 的纸，
//   side=0 表示玩家 1 行动，side=1 表示玩家 2 行动。
//   由于「删除三进制位」必然使数值严格变小，游戏无环，可用记忆化搜索：
//     win(state) = 存在一步能走到「对手必败」的局面。
//   公平局面 = !win(a,b,c,d,0) && !win(a,b,c,d,1)。
//   枚举 a<=b、c<=d（纸内无序），计数。
//
// 缩数据范围：1 <= N <= 50（局面数约 2*(N+1)^4，N=50 时约 1.3e7，瞬间完成）。
// 验证点 F(5)=21 由 verify 命令检查。

// 返回 n 的三进制字符串（最高位在前，无前导零）。
string tern(ll n) {
    string s;
    while (n > 0) { s += char('0' + n % 3); n /= 3; }
    reverse(s.begin(), s.end());
    return s;
}

// 从 n 的三进制表示中删除一个「允许的字符集合 allowed 中的」字符，
// 返回所有合法的新数值。
// 规则（与 PE 882 一致）：删除后若字符串为空，则得到 0；若结果以 0 开头且长度 ≥2，
// 则前导零不允许（该删除无效）；数字 0 是终态（不能再移动）。
vector<ll> succ(ll n, const string& allowed) {
    if (n == 0) return {};                 // 0 是终态，无法移动
    string s = tern(n);
    vector<ll> res;
    for (int i = 0; i < (int)s.size(); i++) {
        if (allowed.find(s[i]) == string::npos) continue;
        string t = s.substr(0, i) + s.substr(i + 1);
        if (t.empty()) { res.push_back(0); continue; }      // 删除最后一位 -> 0
        if (t.size() >= 2 && t[0] == '0') continue;         // 前导零不允许
        ll v = 0;
        for (char c : t) v = v * 3 + (c - '0');
        res.push_back(v);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string line;
    if (!getline(cin, line)) return 0;

    // verify 命令：验证 F(5) = 21
    if (line == "verify") {
        ll N = 5;
        // ---- 计算 F(5) ----
        // 预计算后继
        vector<vector<ll>> s02(N + 1), s12(N + 1);
        for (ll n = 1; n <= N; n++) {
            s02[n] = succ(n, "02");
            s12[n] = succ(n, "12");
        }
        ll K = N + 1;
        // memo: key = (((a*K+b)*K+c)*K+d)*2+side
        vector<int8_t> memo((ll)K * K * K * K * 2, -1);
        auto id = [&](ll a, ll b, ll c, ll d, ll side) {
            return ((((a * K + b) * K + c) * K + d) * 2 + side);
        };
        function<bool(ll,ll,ll,ll,int)> win = [&](ll a, ll b, ll c, ll d, int side) -> bool {
            ll key = id(a, b, c, d, side);
            if (memo[key] != -1) return memo[key] == 1;
            bool res = false;
            if (side == 0) {
                // 玩家1：自己 (a,b) 删 0 或 2；对手 (c,d) 删 1 或 2
                for (ll y : s02[a]) { ll na=y, nb=b; if (na>nb) swap(na,nb); if (!win(na,nb,c,d,1)) { res=true; goto done; } }
                for (ll y : s02[b]) { ll na=a, nb=y; if (na>nb) swap(na,nb); if (!win(na,nb,c,d,1)) { res=true; goto done; } }
                for (ll y : s12[c]) { ll nc=y, nd=d; if (nc>nd) swap(nc,nd); if (!win(a,b,nc,nd,1)) { res=true; goto done; } }
                for (ll y : s12[d]) { ll nc=c, nd=y; if (nc>nd) swap(nc,nd); if (!win(a,b,nc,nd,1)) { res=true; goto done; } }
            } else {
                // 玩家2：自己 (c,d) 删 0 或 2；对手 (a,b) 删 1 或 2
                for (ll y : s12[a]) { ll na=y, nb=b; if (na>nb) swap(na,nb); if (!win(na,nb,c,d,0)) { res=true; goto done; } }
                for (ll y : s12[b]) { ll na=a, nb=y; if (na>nb) swap(na,nb); if (!win(na,nb,c,d,0)) { res=true; goto done; } }
                for (ll y : s02[c]) { ll nc=y, nd=d; if (nc>nd) swap(nc,nd); if (!win(a,b,nc,nd,0)) { res=true; goto done; } }
                for (ll y : s02[d]) { ll nc=c, nd=y; if (nc>nd) swap(nc,nd); if (!win(a,b,nc,nd,0)) { res=true; goto done; } }
            }
        done:
            memo[key] = res ? 1 : 0;
            return res;
        };

        ll F = 0;
        for (ll a = 1; a <= N; a++)
            for (ll b = a; b <= N; b++)
                for (ll c = 1; c <= N; c++)
                    for (ll d = c; d <= N; d++)
                        if (!win(a,b,c,d,0) && !win(a,b,c,d,1)) F++;

        cout << "PE 963: Removing Trits / 移除三进制位  (简单版本)\n\n";
        cout << "=== 验证点 ===\n";
        cout << "题面给出：F(5) = 21\n";
        cout << "计算得到：F(5) = " << F << (F == 21 ? "  ✓" : "  ✗") << "\n";
        cout << "题面给出：(1,5 | 2,4) 是公平局面\n";
        cout << "计算得到：win(1,5,2,4,0) = " << (win(1,5,2,4,0) ? "true" : "false")
             << ", win(1,5,2,4,1) = " << (win(1,5,2,4,1) ? "true" : "false")
             << ((!win(1,5,2,4,0) && !win(1,5,2,4,1)) ? "  ✓" : "  ✗") << "\n";
        return 0;
    }

    // 参数化：读入 N，输出 F(N)
    ll N;
    stringstream ss(line);
    if (!(ss >> N) || N < 1 || N > 50) {
        cout << "用法: 输入整数 N (1<=N<=50)，输出 F(N)。\n";
        cout << "或输入 'verify' 运行验证 (F(5)=21)。\n";
        return 0;
    }

    vector<vector<ll>> s02(N + 1), s12(N + 1);
    for (ll n = 1; n <= N; n++) {
        s02[n] = succ(n, "02");
        s12[n] = succ(n, "12");
    }
    ll K = N + 1;
    vector<int8_t> memo((ll)K * K * K * K * 2, -1);
    auto id = [&](ll a, ll b, ll c, ll d, ll side) {
        return ((((a * K + b) * K + c) * K + d) * 2 + side);
    };
    function<bool(ll,ll,ll,ll,int)> win = [&](ll a, ll b, ll c, ll d, int side) -> bool {
        ll key = id(a, b, c, d, side);
        if (memo[key] != -1) return memo[key] == 1;
        bool res = false;
        if (side == 0) {
            for (ll y : s02[a]) { ll na=y, nb=b; if (na>nb) swap(na,nb); if (!win(na,nb,c,d,1)) { res=true; goto done; } }
            for (ll y : s02[b]) { ll na=a, nb=y; if (na>nb) swap(na,nb); if (!win(na,nb,c,d,1)) { res=true; goto done; } }
            for (ll y : s12[c]) { ll nc=y, nd=d; if (nc>nd) swap(nc,nd); if (!win(a,b,nc,nd,1)) { res=true; goto done; } }
            for (ll y : s12[d]) { ll nc=c, nd=y; if (nc>nd) swap(nc,nd); if (!win(a,b,nc,nd,1)) { res=true; goto done; } }
        } else {
            for (ll y : s12[a]) { ll na=y, nb=b; if (na>nb) swap(na,nb); if (!win(na,nb,c,d,0)) { res=true; goto done; } }
            for (ll y : s12[b]) { ll na=a, nb=y; if (na>nb) swap(na,nb); if (!win(na,nb,c,d,0)) { res=true; goto done; } }
            for (ll y : s02[c]) { ll nc=y, nd=d; if (nc>nd) swap(nc,nd); if (!win(a,b,nc,nd,0)) { res=true; goto done; } }
            for (ll y : s02[d]) { ll nc=c, nd=y; if (nc>nd) swap(nc,nd); if (!win(a,b,nc,nd,0)) { res=true; goto done; } }
        }
    done:
        memo[key] = res ? 1 : 0;
        return res;
    };

    ll F = 0;
    for (ll a = 1; a <= N; a++)
        for (ll b = a; b <= N; b++)
            for (ll c = 1; c <= N; c++)
                for (ll d = c; d <= N; d++)
                    if (!win(a,b,c,d,0) && !win(a,b,c,d,1)) F++;

    cout << F << "\n";
    return 0;
}
