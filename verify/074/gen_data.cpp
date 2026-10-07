#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int, int>> test_cases(10);

    // 1: 样例 — 原题: N=1000000, K=60 → 402
    test_cases[0] = {1000000, 60};

    // 2-3: 小数据
    test_cases[1] = {100, 5};
    test_cases[2] = {1000, 10};

    // 4-6: 大数据
    test_cases[3] = {1000000, 1};
    test_cases[4] = {1000000, 30};
    test_cases[5] = {500000, 60};

    // 7-8: 边界
    test_cases[6] = {1, 1};        // 最小值
    test_cases[7] = {1000000, 60}; // 最大值

    // 9-10: 随机
    for (int i = 8; i < 10; i++) {
        test_cases[i] = {rand_ll(10000, 1000000), rand_ll(1, 60)};
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i].first << " K=" << test_cases[i].second << "\n";
    }

    return 0;
}
