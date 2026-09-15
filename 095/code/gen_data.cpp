#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1: 样例 (N=300, should have amicable pair 220-284, chain min=220)
    test_cases[0] = 300;

    // 2-3: 小数据
    test_cases[1] = rand_ll(300, 10000);
    test_cases[2] = rand_ll(10000, 50000);

    // 4-6: 中等数据
    test_cases[3] = rand_ll(50000, 200000);
    test_cases[4] = rand_ll(200000, 500000);
    test_cases[5] = rand_ll(500000, 800000);

    // 7-8: 大数据
    test_cases[6] = rand_ll(800000, 950000);
    test_cases[7] = rand_ll(950000, 999999);

    // 9: 最大值 (PE原题)
    test_cases[8] = 1000000;

    // 10: 随机
    test_cases[9] = rand_ll(2, 1000000);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
