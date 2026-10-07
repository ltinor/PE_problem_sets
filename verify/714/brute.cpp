// PE714 暴力 (独立验证, 定义直译, 仅限小 K)
// 按值升序扫描所有双字数, 对每个未定 n 试除; 全部 found 后的 D(K) 与 std 对拍.
// 双字数判定: 数字掩码 popcount <= 2. 扫描上限 1e8 (n<=200 的 d(n) 远小于此).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

static bool duodigit(ll v) {
    int mask = 0, cnt = 0;
    while (v > 0) {
        int b = 1 << (v % 10);
        if (!(mask & b)) { mask |= b; if (++cnt > 2) return false; }
        v /= 10;
    }
    return true;
}

static string i128str(i128 v) {
    if (v == 0) return "0";
    string s; while (v > 0) { s += char('0' + (int)(v % 10)); v /= 10; }
    reverse(s.begin(), s.end()); return s;
}

int main() {
    ll K;
    if (!(cin >> K)) return 0;
    vector<bool> found(K + 1, false);
    vector<i128> dval(K + 1, -1);
    int remaining = (int)K;
    const ll VMAX = 100000000LL;
    for (ll v = 1; v <= VMAX && remaining > 0; v++) {
        if (!duodigit(v)) continue;
        for (ll n = 1; n <= K; n++) {
            if (!found[n] && v % n == 0) {
                found[n] = true; dval[n] = v; remaining--;
            }
        }
    }
    if (remaining > 0) { cout << "UNSCANNED " << remaining << "\n"; return 1; }
    i128 total = 0;
    for (ll n = 1; n <= K; n++) total += dval[n];
    cout << i128str(total) << "\n";
    return 0;
}
