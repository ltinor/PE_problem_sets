#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    // 10 组测试数据 (n, k)，k 为奇数
    vector<pair<int, int>> test_cases = {
        {2, 3},   // 样例 G(2,3)=14
        {4, 3},   // G(4,3)=496
        {1, 1},   // 边界
        {1, 3},
        {1, 5},
        {2, 1},
        {2, 5},
        {3, 1},
        {3, 3},   // G(3,3)=80
        {4, 5},   // 最大数据 G(4,5)=79274
    };

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with (n,k) = ("
             << test_cases[i].first << "," << test_cases[i].second << ")\n";
    }

    return 0;
}
