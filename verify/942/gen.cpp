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

    ll q;
    if (mode == "small") {
        q = rand_ll(2, 20);   // 缩数据：p = 2^q-1 <= 1e6，秒出
    } else {
        q = rand_ll(2, 30);   // p <= 1e9
    }
    cout << q << "\n";
    return 0;
}
