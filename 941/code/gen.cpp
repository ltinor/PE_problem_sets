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

    int k, n;
    if (mode == "small") {
        // 缩数据：k^n <= 1e5，秒出
        k = rand_ll(2, 4);
        n = rand_ll(2, 4);
        while (true) {
            ll t = 1; for (int i = 0; i < n; i++) t *= k;
            if (t <= 100000) break;
            n--;
        }
    } else {
        k = rand_ll(2, 6);
        n = rand_ll(2, 6);
    }
    cout << k << " " << n << "\n";
    return 0;
}
