#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1-2: 小数据（可手动验证）
    test_cases[0] = 3;
    test_cases[1] = 10;

    // 3-4: 中等
    test_cases[2] = 50;
    test_cases[3] = 100;

    // 5-6: 大
    test_cases[4] = 500;
    test_cases[5] = 1000;

    // 7-8: PE原题/边界
    test_cases[6] = 5000;  // PE原题答案: 2868868
    test_cases[7] = 1;

    // 9-10: 更多
    test_cases[8] = 30;
    test_cases[9] = 200;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
