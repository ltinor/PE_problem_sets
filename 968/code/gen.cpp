#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * (long long)rand() % (r - l + 1);
}

// 生成一行 10 个整数（0..15），表示 10 个两两和上界
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int lo = 0, hi = 15;
    if (mode == "small") { lo = 0; hi = 15; }
    else if (mode == "large") { lo = 8; hi = 15; }

    for (int i = 0; i < 10; i++) {
        if (i) cout << " ";
        cout << rand_ll(lo, hi);
    }
    cout << "\n";
    return 0;
}
