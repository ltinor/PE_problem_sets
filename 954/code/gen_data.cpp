#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1 样例
    test_cases[0] = 100;

    // 2-3 小数据 (n <= 10000)
    for (int i = 1; i < 3; i++) {
        test_cases[i] = rand_ll(1, 10000);
    }

    // 4-6 大数据 (n 接近上界 1e6)
    for (int i = 3; i < 6; i++) {
        test_cases[i] = rand_ll(1000000 - 100000, 1000000);
    }

    // 7-8 边界条件
    test_cases[6] = 1;              // 最小值
    test_cases[7] = 1000000LL;      // 最大值

    // 9-10 随机数
    for (int i = 8; i < 10; i++) {
        test_cases[i] = rand_ll(1, 1000000LL);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }

    return 0;
}
