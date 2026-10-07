#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * (ll)rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand((unsigned)time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll n;
    if (mode == "small") {
        n = rand_ll(1, 100000);        // 对拍用小数据
    } else {
        n = rand_ll(1, 10000000LL);    // 大数据
    }

    assert(n >= 1 && n <= 10000000LL);
    cout << n << "\n";
    return 0;
}
