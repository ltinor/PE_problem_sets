#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    vector<pair<int,int>> test_cases(10);

    // 1-2: 小网格（可暴力验证）
    test_cases[0] = {2, 3};
    test_cases[1] = {3, 3};

    // 3-4: 中等
    test_cases[2] = {2, 9};  // 已知41种
    test_cases[3] = {3, 6};

    // 5-6: 更大
    test_cases[4] = {4, 6};
    test_cases[5] = {6, 6};

    // 7-8: PE原题/边界
    test_cases[6] = {9, 12}; // PE原题答案: 20574308184277971
    test_cases[7] = {3, 4};

    // 9-10: 更多
    test_cases[8] = {3, 8};
    test_cases[9] = {4, 9};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with " << test_cases[i].first
             << "x" << test_cases[i].second << "\n";
    }

    return 0;
}
