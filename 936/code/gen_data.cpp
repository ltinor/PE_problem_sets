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
    test_cases[0] = 10;

    // 2-3 小数据
    test_cases[1] = 3;
    test_cases[2] = 7;

    // 4-6 较大数据
    test_cases[3] = 12;
    test_cases[4] = 13;
    test_cases[5] = 14;

    // 7-8 边界条件
    test_cases[6] = 3;   // 最小值
    test_cases[7] = 15;  // 最大值

    // 9-10 随机数
    test_cases[8] = rand_ll(3, 15);
    test_cases[9] = rand_ll(3, 15);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }

    return 0;
}
