// PE006: 平方和与和平方之差
// K <= 1e5 时答案可达 ~2.5e19, 超出 long long, 用 __int128 输出
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void print_i128(__int128 x) {
    if (x == 0) { cout << "0"; return; }
    if (x < 0) { cout << "-"; x = -x; }
    string s;
    while (x) { s += char('0' + (int)(x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        ll K;
        cin >> K;
        ll sum = K * (K + 1) / 2;
        ll sum_sq = K * (K + 1) * (2*K + 1) / 6;
        print_i128((__int128)sum * sum - sum_sq);
        cout << "\n";
    }
    return 0;
}
