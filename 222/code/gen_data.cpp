#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct Case { int N, R; };
    vector<Case> test_cases(10);

    // 1 样例：PE 原题
    test_cases[0] = {21, 50};

    // 2-3 小数据
    test_cases[1] = {2, 50};
    test_cases[2] = {3, 50};

    // 4-5 中数据
    test_cases[3] = {5, 50};
    test_cases[4] = {8, 50};

    // 6-7 稍大数据
    test_cases[5] = {12, 50};
    test_cases[6] = {16, 50};

    // 8-9 不同 R
    test_cases[7] = {10, 55};
    test_cases[8] = {6, 45};

    // 10 边界
    test_cases[9] = {4, 50};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].N << " " << test_cases[i].R << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i].N
             << " R=" << test_cases[i].R << "\n";
    }

    return 0;
}
