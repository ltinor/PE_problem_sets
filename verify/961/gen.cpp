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

    // PE 961 缩数据版：数据范围 N <= 1e6
    ll n;
    if (mode == "small") {
        n = rand_ll(1, 10000);
    } else {
        n = rand_ll(10001, 1000000);
    }

    cout << n << "\n";
    return 0;
}
