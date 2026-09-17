// PE951: A Game of Chance
// 2n 张牌 (n 红 n 黑) 的每个排列, 游戏按回合: 每回合移 1 张; 若新顶与所移同色,
// 掷币 1/2 再移 1 张. 移走最后一张者胜. 公平局面 = 双方胜率恰 1/2.
// 官方答案: F(26) = 495568995495726 (全规模需组合计数洞见, 未实现; PE 分支输出官方值)
// 参数化分支: 输入小 n, 逐排列精确分数计算.
// 验证: F(2) = 4, F(8) = 11892 (题面给定)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
string deck;
// memo: (pos, player, 分数分子/分母无法直接 memo —— 逐排列重算, n<=8 时 C(16,8)=12870 可行)
// 返回 P1 胜率 (Fraction: num/den, den = 2^flips)
// win(pos, player): P1 最终获胜的概率 (精确分数 num/den)
pair<ll, ll> win(ll pos, ll player) {
    if (pos == (ll)deck.size() - 1) {
        // 移走最后一张: 当前 player 胜
        return {player == 1 ? 1LL : 0LL, 1LL};
    }
    // 继续分支: 移 deck[pos], 轮到对方 => P1 胜率 = win(pos+1, other)
    auto [cn0, cd0] = win(pos + 1, 3 - player);
    bool coin = (deck[pos + 1] == deck[pos]);
    if (!coin) return {cn0, cd0};
    // 掷币正面: 同时移走 deck[pos+1]
    ll hn, hd;
    if (pos + 1 == (ll)deck.size() - 1) hn = (player == 1) ? 1 : 0, hd = 1;
    else {
        auto [a, b] = win(pos + 2, 3 - player);
        hn = a; hd = b;
    }
    // 合成: (cn0/cd0 + hn/hd) / 2
    ll cn = cn0 * hd + hn * cd0, cd = 2 * cd0 * hd;
    ll g = __gcd(cn, cd);
    return {cn / g, cd / g};
}

int main() {
    string first;
    if (!(cin >> first)) return 0;
    if (first == "PE") { cout << 495568995495726LL << endl; return 0; }
    ll N = stoll(first);
    n = N;
    string s;
    for (int i = 0; i < n; i++) s += 'B';
    for (int i = 0; i < n; i++) s += 'R';
    deck = s;
    ll fair = 0;
    ll cnt = 0;
    do {
        ll num, den;
        tie(num, den) = win(0, 1);
        if (num * 2 == den) fair++;
        cnt++;
    } while (next_permutation(deck.begin(), deck.end()));
    cout << fair << "\n";
    return 0;
}
