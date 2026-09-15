#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 942 暴力验证：从 x=1 线性枚举到 p-1，找最小的 x 使 x^2 ≡ q (mod p)。
// 用于 check.sh 与 std.cpp 对拍。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll q;
    if (!(cin >> q)) return 0;

    i128 p = ((i128)1 << q) - 1;
    for (i128 x = 1; x < p; x++) {
        if (x * x % p == q % p) {
            cout << (ll)x << "\n";
            return 0;
        }
    }
    cout << -1 << "\n";
    return 0;
}
