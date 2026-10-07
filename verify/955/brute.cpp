#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 朴素版（用于对拍）：直接按递推式一步步走，不引入"相邻项差"的优化，
// 判断三角形数用简单开方，与 std.cpp 相互独立。

bool is_tri(ll x) {
    // x == m(m+1)/2  <=>  (2m+1)^2 == 8x+1
    long double t = (sqrtl(8.0L * (long double)x + 1.0L) - 1.0L) / 2.0L;
    ll m = (ll)llround(t);
    for (ll c = m - 2; c <= m + 2; c++) {
        if (c >= 0 && c * (c + 1) / 2 == x) return true;
    }
    return false;
}

int main(){
    ll k;
    cin >> k;

    if (k <= 1) { cout << 0 << "\n"; return 0; } // a_0 = 3 是第 1 个三角形数

    ll prev = 0;   // 未定义时不影响，这里从 a_0=3, a_1=4 起步
    ll cur  = 3;   // a_0
    ll nxt  = 4;   // a_1 = a_0 + 1（3 是三角形数）
    ll idx  = 1;   // 当前指向 a_1
    ll cnt  = 1;   // 已发现 1 个三角形数（a_0）

    prev = cur;
    cur  = nxt;
    if (is_tri(cur)) cnt++;

    while (cnt < k) {
        if (is_tri(cur)) nxt = cur + 1;
        else             nxt = 2 * cur - prev + 1;
        prev = cur;
        cur  = nxt;
        idx++;
        if (is_tri(cur)) cnt++;
    }

    cout << idx << "\n";
    return 0;
}
