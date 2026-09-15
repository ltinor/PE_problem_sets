#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1 样例：PE 原题
    test_cases[0] = 100;

    // 2-3 小数据
    test_cases[1] = 2;
    test_cases[2] = 3;

    // 4-5 中数据
    test_cases[3] = 5;
    test_cases[4] = 10;

    // 6-7 稍大数据
    test_cases[5] = 20;
    test_cases[6] = 50;

    // 8-9 边界
    test_cases[7] = 1;
    test_cases[8] = 80;

    // 10 随机
    test_cases[9] = rand_int(10, 90);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with S = " << test_cases[i] << "\n";
    }

    return 0;
}
