#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 963 (简单版本): Removing Trits / 移除三进制位
//
// 原题求 F(10^5)。这里把数据缩小到 N <= 100, 用「记忆化博弈搜索」直接算 F(N)。
//
// 博弈规则:
//   每位玩家手上一张纸, 上面有两个正整数。轮到某玩家时:
//     - 从自己纸上的数里移除一个三进制 '0';
//     - 从对手纸上的数里移除一个三进制 '1';
//     - 从任意一方的数里移除一个三进制 '2'。
//   移除后得到的数不能有前导零(去掉前导零); 把最后一个数位删掉时得到 0。
//   无法行动者输。先手必败的局面称为 "公平" 局面。
//   F(N) = 所有数都不超过 N 的公平局面个数(同一张纸上两数顺序不计, 两张纸顺序计入)。
//   验证点: F(5) = 21。
//
// 算法:
//   局面由 4 个数 (a,b | c,d) 描述, a,b 属于先手, c,d 属于后手(各自无序)。
//   每一步只改变一个数, 因此是四个独立分量的析取和; 但「先手能删 0/2、后手能删 1/2」
//   使得每个分量对先手/后手的可移动集合不同——这是 partizan 游戏, 不能简单用 Grundy 异或。
//   这里直接做博弈树记忆化搜索:
//     W(a,b,c,d) = 先手(拥有 a,b)是否有必胜策略。
//   对称性: 先手在 (a,b,c,d) 行动后, 轮到后手; 后手必胜 == W(后手新对, 先手新对)。
//     先手移动自己 a 去掉某位 -> r: 新局面 (r,b,c,d), 后手必胜当且仅当 W(c,d,min(r,b),max(r,b))。
//     先手移动对手 c 去掉某位 -> r: 新局面 (a,b,r,d), 后手必胜当且仅当 W(min(r,d),max(r,d),a,b)。
//   公平 = !W(a,b,c,d) && !W(c,d,a,b)。
//
// 复杂度: O(N^4) 个局面(用无序对索引压缩), 每局面分支 O(log3 N)。

static int N;
static vector<vector<vector<int>>> rem; // rem[d][x]: 从 x 移除一个三进制 d 可得到的数集合
static vector<char> memo;               // W 的记忆化: -1 未知, 0 后手胜, 1 先手胜
static ll P;                            // 无序对个数

// 三进制表示(最高位在前)
string tern(ll n) {
    if (n == 0) return "0";
    string s;
    while (n > 0) { s += char('0' + (n % 3)); n /= 3; }
    reverse(s.begin(), s.end());
    return s;
}

// 无序对 (x<=y) 的索引
ll pairIdx(int x, int y) {
    // 0 <= x <= y <= N
    return (ll)x * (N + 1) - (ll)x * (x - 1) / 2 + (y - x);
}

// W(a,b,c,d): 先手(拥有 a,b, 且 a<=b)是否有必胜策略; 后手拥有 (c,d), c<=d
char W(int a, int b, int c, int d) {
    ll key = pairIdx(a, b) * P + pairIdx(c, d);
    if (memo[key] != -1) return memo[key];

    // 先手移动自己的数 (a 或 b): 移除 0 或 2
    for (int r : rem[0][a]) {
        int na = min(r, b), nb = max(r, b);
        if (!W(c, d, na, nb)) return memo[key] = 1;
    }
    for (int r : rem[2][a]) {
        int na = min(r, b), nb = max(r, b);
        if (!W(c, d, na, nb)) return memo[key] = 1;
    }
    for (int r : rem[0][b]) {
        int na = min(a, r), nb = max(a, r);
        if (!W(c, d, na, nb)) return memo[key] = 1;
    }
    for (int r : rem[2][b]) {
        int na = min(a, r), nb = max(a, r);
        if (!W(c, d, na, nb)) return memo[key] = 1;
    }

    // 先手移动对手的数 (c 或 d): 移除 1 或 2
    for (int r : rem[1][c]) {
        int nc = min(r, d), nd = max(r, d);
        if (!W(nc, nd, a, b)) return memo[key] = 1;
    }
    for (int r : rem[2][c]) {
        int nc = min(r, d), nd = max(r, d);
        if (!W(nc, nd, a, b)) return memo[key] = 1;
    }
    for (int r : rem[1][d]) {
        int nc = min(c, r), nd = max(c, r);
        if (!W(nc, nd, a, b)) return memo[key] = 1;
    }
    for (int r : rem[2][d]) {
        int nc = min(c, r), nd = max(c, r);
        if (!W(nc, nd, a, b)) return memo[key] = 1;
    }

    return memo[key] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    N = (int)n;

    // 预处理每个数的可移动集合
    rem.assign(3, vector<vector<int>>(N + 1));
    for (int x = 0; x <= N; x++) {
        string s = tern(x);
        int L = (int)s.size();
        for (int i = 0; i < L; i++) {
            int d = s[i] - '0';
            string t = s.substr(0, i) + s.substr(i + 1);
            int r;
            if (t.empty()) {
                r = 0;
            } else {
                size_t p = t.find_first_not_of('0');
                if (p == string::npos) r = 0;
                else r = (int)stoi(t.substr(p), nullptr, 3);
            }
            if (r == x) continue;
            bool dup = false;
            for (int v : rem[d][x]) if (v == r) { dup = true; break; }
            if (!dup) rem[d][x].push_back(r);
        }
    }

    // 记忆化数组
    P = (ll)(N + 1) * (N + 2) / 2;
    memo.assign(P * P, -1);

    // 枚举所有初始局面 (同一张纸上的两数无序)
    ll ans = 0;
    for (int a = 1; a <= N; a++) {
        for (int b = a; b <= N; b++) {
            for (int c = 1; c <= N; c++) {
                for (int d = c; d <= N; d++) {
                    if (!W(a, b, c, d) && !W(c, d, a, b)) ans++;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
