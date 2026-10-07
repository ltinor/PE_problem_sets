#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1 样例
    test_cases[0] = 5;

    // 2-3 小数据 (K ≤ 10)
    for (int i = 1; i < 3; i++) {
        test_cases[i] = rand_ll(1, 10);
    }

    // 4-6 中等数据 (K ≤ 100)
    for (int i = 3; i < 6; i++) {
        test_cases[i] = rand_ll(10, 100);
    }

    // 7-8 边界条件
    test_cases[6] = 1;        // 最小值
    test_cases[7] = 1000;     // 最大值

    // 9-10 大数据 (K ≤ 1000)
    for (int i = 8; i < 10; i++) {
        test_cases[i] = rand_ll(500, 1000);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
