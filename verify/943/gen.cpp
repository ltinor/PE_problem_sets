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

    ll a, b, N;
    if (mode == "small") {
        a = rand_ll(2, 9);
        do { b = rand_ll(2, 9); } while (b == a);
        N = rand_ll(1, 10000);   // 缩数据：N <= 1e4，秒出
    } else {
        a = rand_ll(2, 20);
        do { b = rand_ll(2, 20); } while (b == a);
        N = rand_ll(1, 1000000); // N <= 1e6
    }
    cout << a << " " << b << " " << N << "\n";
    return 0;
}
