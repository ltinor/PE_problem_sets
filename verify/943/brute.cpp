#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 943 暴力验证：按定义直接生成整条数列再求和。
// 生成规则：seq[0..a-1] = a（第 0 段是 a 个 a）；
// 之后第 j 段（j=1,2,...）的长度为 seq[j]，符号为「j 偶 ? a : b」，
// 逐段追加直到长度 >= N。与 std.cpp 逻辑等价，独立书写用于对拍。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b, N;
    if (!(cin >> a >> b >> N)) return 0;

    vector<ll> seq;
    seq.reserve(N + 16);
    for (int i = 0; i < a; i++) seq.push_back(a);

    int j = 1;
    while ((ll)seq.size() < N) {
        ll len = seq[j];
        ll sym = (j % 2 == 0) ? a : b;
        for (ll t = 0; t < len; t++) seq.push_back(sym);
        j++;
    }

    ll sum = 0;
    for (ll i = 0; i < N; i++) sum += seq[i];
    cout << sum << "\n";
    return 0;
}
