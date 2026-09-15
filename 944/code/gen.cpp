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
        n = rand_ll(1, 16);        // 缩数据：n <= 16，秒出
    } else {
        n = rand_ll(1, 10000000);  // n <= 1e7（O(sqrt n) 分块）
    }
    cout << n << "\n";
    return 0;
}
