#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 暴力: 枚举 n = 1..N, 计算其所有 ≤ B 的不同质因数之和, 判断是否被 3 整除。
// 仅用于小数据下与 std 对拍 (N ≤ 1e6, B ≤ 40)。

int main() {
    ll N; int B;
    cin >> N >> B;

    vector<int> ps;
    for (int i = 2; i <= B; i++) {
        bool ok = true;
        for (int p : ps) {
            if (p * p > i) break;
            if (i % p == 0) { ok = false; break; }
        }
        if (ok) ps.push_back(i);
    }

    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        ll s = 0;
        for (int p : ps) if (n % p == 0) s += p;
        if (s % 3 == 0) cnt++;
    }
    cout << cnt << "\n";
    return 0;
}
