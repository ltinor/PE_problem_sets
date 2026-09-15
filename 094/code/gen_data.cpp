#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1: 样例 (M=100, should get 16+50=66? Let's compute...)
    // a=5: P=16, a=17: P=50 → sum=66
    test_cases[0] = 100;

    // 2-3: 小数据
    test_cases[1] = rand_ll(100, 10000);
    test_cases[2] = rand_ll(10000, 100000);

    // 4-6: 中等数据
    test_cases[3] = rand_ll(100000, 1000000);
    test_cases[4] = rand_ll(1000000, 10000000);
    test_cases[5] = rand_ll(10000000, 100000000);

    // 7-8: 大数据 (接近上界)
    test_cases[6] = rand_ll(100000000, 500000000);
    test_cases[7] = rand_ll(500000000, 999999999);

    // 9: 最大值 (PE原题)
    test_cases[8] = 1000000000LL;

    // 10: 随机
    test_cases[9] = rand_ll(1, 1000000000LL);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}
