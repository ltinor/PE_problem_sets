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

    // 1 样例 (S(10)=310897)
    test_cases[0] = 10;

    // 2-3 小数据 (M <= 100)
    test_cases[1] = rand_int(1, 50);
    test_cases[2] = rand_int(1, 100);

    // 4-6 大数据 (M 接近上界 1000)
    test_cases[3] = rand_int(900, 1000);
    test_cases[4] = rand_int(900, 1000);
    test_cases[5] = rand_int(500, 1000);

    // 7-8 边界条件
    test_cases[6] = 1;      // 最小值
    test_cases[7] = 1000;   // 最大值

    // 9-10 随机
    test_cases[8] = rand_int(1, 1000);
    test_cases[9] = rand_int(1, 1000);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }
    return 0;
}
