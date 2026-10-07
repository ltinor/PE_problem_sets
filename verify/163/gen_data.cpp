#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1-2: 小数据（可暴力验证）
    test_cases[0] = 1;   // T(1)=16
    test_cases[1] = 2;   // T(2)=104

    // 3-4: 中等
    test_cases[2] = 3;
    test_cases[3] = 5;

    // 5-6: 大
    test_cases[4] = 10;
    test_cases[5] = 20;

    // 7-8: PE原题/边界
    test_cases[6] = 36;  // PE原题答案: 343047
    test_cases[7] = 1;   // 边界

    // 9-10: 更多
    test_cases[8] = 8;
    test_cases[9] = 15;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
