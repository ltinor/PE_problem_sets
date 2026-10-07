#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1-2: 小数据
    test_cases[0] = 3;
    test_cases[1] = 5;

    // 3-4: 中等
    test_cases[2] = 10;
    test_cases[3] = 15;

    // 5-6: 接近上限
    test_cases[4] = 19;
    test_cases[5] = 20;  // PE原题答案: 378158756814587

    // 7-8: 边界
    test_cases[6] = 1;
    test_cases[7] = 2;

    // 9-10: 随机
    test_cases[8] = 8;
    test_cases[9] = 12;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
