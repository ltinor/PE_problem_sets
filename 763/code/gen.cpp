#include <bits/stdc++.h>
using namespace std;

// 数据生成器: 输出一个整数 N (分裂次数)。
//   small: 1 <= N <= 12   (与暴力对拍可用)
//   large: 13 <= N <= 20  (数据范围上界)

static long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main(int argc, char *argv[]) {
    srand((unsigned)time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long n;
    if (mode == "small") {
        n = rand_ll(1, 12);
    } else if (mode == "large") {
        n = rand_ll(13, 20);
    } else {
        n = rand_ll(1, 20);
    }

    assert(n >= 1 && n <= 20);
    cout << n << "\n";
    return 0;
}
