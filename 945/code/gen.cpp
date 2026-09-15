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

    ll N;
    if (mode == "small") {
        N = rand_ll(0, 200);   // 对拍用：小 N，std/brute 都秒出
    } else {
        N = rand_ll(0, 5000);  // 缩数据上限
    }
    cout << N << "\n";
    return 0;
}
