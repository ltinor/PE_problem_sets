#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1 样例 M=7 -> ans=5
    test_cases[0] = 7;

    // 2-3 小数据
    test_cases[1] = 1;
    test_cases[2] = 2;

    // 4-6 中等数据
    for (int i = 3; i < 6; i++) {
        test_cases[i] = rand_ll(10, 100);
    }

    // 7-8 边界
    test_cases[6] = 3;
    test_cases[7] = 1000;

    // 9-10 随机
    for (int i = 8; i < 10; i++) {
        test_cases[i] = rand_ll(100, 999);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << "1\n" << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}
