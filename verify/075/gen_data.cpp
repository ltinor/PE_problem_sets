#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: 样例 — 原题: M=1500000 → 161667
    test_cases[0] = 1500000;

    // 2-3: 小数据
    test_cases[1] = 12;
    test_cases[2] = 120;

    // 4-6: 中大数据
    test_cases[3] = 1000;
    test_cases[4] = 100000;
    test_cases[5] = 500000;

    // 7-8: 边界
    test_cases[6] = 12;              // 最小值
    test_cases[7] = 1500000;        // 最大值

    // 9-10: 随机
    for (int i = 8; i < 10; i++) {
        test_cases[i] = rand_ll(10000, 1500000);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M=" << test_cases[i] << "\n";
    }

    return 0;
}
