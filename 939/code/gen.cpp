#include <bits/stdc++.h>
using namespace std;

// PE 939 数据生成器：生成单个参数 N。
//   small: N in [1, 12]（用于与 brute 对照）
//   large: N in [1, 500]（缩数据上界）
long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand((unsigned)time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long n;
    if (mode == "small") {
        n = rand_ll(1, 12);
    } else {
        n = rand_ll(1, 500);
    }
    assert(n >= 1);
    cout << n << "\n";
    return 0;
}
