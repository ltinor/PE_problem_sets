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

    ll k;
    if (mode == "small") {
        k = rand_ll(2, 15);        // 缩数据：k <= 15（f_15=610，秒出）
    } else {
        k = rand_ll(2, 20);        // 最大支持 k=20（f_20=6765）
    }
    cout << k << "\n";
    return 0;
}
