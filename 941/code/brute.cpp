#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 941 暴力验证：枚举所有长度 1..n 的串（字典序），显式判断是否为
// Lyndon 词（本原且是最小旋转），拼接长度整除 n 者，得到与 std 相同的 C(k,n)。
// 用于 check.sh 与 std.cpp 对拍。

bool is_lyndon(const string &s) {
    int L = (int)s.size();
    string best = s;
    for (int i = 1; i < L; i++) {
        string r = s.substr(i) + s.substr(0, i);
        if (r < best) best = r;
        if (r == s) return false; // 非本原
    }
    return best == s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    if (!(cin >> k >> n)) return 0;

    string concat;
    function<void(string)> dfs = [&](string s) {
        if (!s.empty() && n % (int)s.size() == 0 && is_lyndon(s)) concat += s;
        if ((int)s.size() == n) return;
        for (int c = 0; c < k; c++) dfs(s + char('0' + c));
    };
    dfs("");

    ll total = 1;
    for (int i = 0; i < n; i++) total *= k;
    string ans;
    ans.reserve(total + n - 1);
    for (ll i = 0; i < total + n - 1; i++) ans.push_back(concat[i % concat.size()]);

    cout << ans << "\n";
    return 0;
}
