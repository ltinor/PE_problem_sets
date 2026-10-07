#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 961 brute：独立实现（字符串逐位删除 + 递归记忆化），
// 用于与 std 的整数运算 DP 交叉验证。

int grundy(ll n, unordered_map<ll, int>& memo) {
    if (n == 0) return 0;
    auto it = memo.find(n);
    if (it != memo.end()) return it->second;

    string s = to_string(n);
    bool seen[64] = {false};
    for (int i = 0; i < (int)s.size(); i++) {
        string t = s.substr(0, i) + s.substr(i + 1);
        ll m = 0;
        for (char c : t) m = m * 10 + (c - '0');   // 自动去掉前导零
        seen[grundy(m, memo)] = true;
    }
    int mex = 0;
    while (seen[mex]) mex++;
    memo[n] = mex;
    return mex;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    if (!(cin >> N)) return 0;

    unordered_map<ll, int> memo;
    ll ans = 0;
    for (ll n = 1; n < N; n++) {
        if (grundy(n, memo) != 0) ans++;
    }
    cout << ans << "\n";
    return 0;
}
