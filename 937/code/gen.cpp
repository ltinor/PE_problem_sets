#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char *argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll n;
    if (mode == "small") {
        n = rand_ll(1, 2000);     // 缩数据：供 brute 交叉验证（O(n·π(n))）
    } else {
        n = rand_ll(1, 1000000);  // OJ 数据范围上限
    }
    cout << n << "\n";
    return 0;
}
