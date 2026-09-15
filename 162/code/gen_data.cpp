#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1-2: 小数据
    test_cases[0] = 3;
    test_cases[1] = 5;

    // 3-4: 中等
    test_cases[2] = 8;
    test_cases[3] = 12;

    // 5-6: 大/PE原题
    test_cases[4] = 15;
    test_cases[5] = 16;  // PE原题答案: 3D58725572C62302

    // 7-8: 边界
    test_cases[6] = 1;
    test_cases[7] = 2;

    // 9-10: 更多
    test_cases[8] = 4;
    test_cases[9] = 10;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with D = " << test_cases[i] << "\n";
    }

    return 0;
}
