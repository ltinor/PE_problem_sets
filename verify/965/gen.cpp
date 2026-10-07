#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) % (r - l + 1);
}

int main(int argc, char *argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long n;

    if (mode == "small") {
        n = rand_ll(1, 200);          // 小数据，供 brute 对拍
    } else if (mode == "large") {
        n = rand_ll(1, 10000);        // 缩数据后的上界
    }

    assert(n >= 1 && n <= 10000);

    cout << n << "\n";
}
