#include <bits/stdc++.h>
using namespace std;

// 随机生成单个测试输入 N（0 <= N <= 20）。
//   small: 小数据，用于 std/brute 对拍（brute 为 std::set 暴力，只适合小 N）
//   large: 较大数据

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long n;
    if (mode == "small") {
        n = rand_ll(0, 12);
    } else {
        n = rand_ll(13, 20);
    }

    cout << n << "\n";
    return 0;
}
