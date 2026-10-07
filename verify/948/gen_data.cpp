#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0) ^ getpid());

    vector<int> test_cases(10);

    // 1 样例 (F(8)=181)
    test_cases[0] = 8;

    // 2-3 小数据 (n <= 12)
    test_cases[1] = 3;             // F(3)=4
    test_cases[2] = rand_int(4, 12);

    // 4-6 大数据 (n 接近上界 24)
    test_cases[3] = rand_int(20, 24);
    test_cases[4] = rand_int(20, 24);
    test_cases[5] = rand_int(16, 24);

    // 7-8 边界条件
    test_cases[6] = 1;             // 最小值 F(1)=0
    test_cases[7] = 24;            // 最大值

    // 9-10 随机
    test_cases[8] = rand_int(1, 24);
    test_cases[9] = rand_int(1, 24);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }
    return 0;
}
