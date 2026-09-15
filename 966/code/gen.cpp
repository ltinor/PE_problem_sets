#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    long long maxc = 100;  // 简单版：边长上限（缩数据）
    if (argc > 1) maxc = atoll(argv[1]);

    long long a, b, c;
    // 生成满足 1<=a<=b<=c 且 a+b>c 的合法三角形
    do {
        c = rand_ll(2, maxc);
        b = rand_ll(1, c);
        a = rand_ll(1, b);
    } while (a + b <= c);

    cout << a << " " << b << " " << c << "\n";
}
