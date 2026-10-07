#include <bits/stdc++.h>
using namespace std;

// PE 939 数据生成器：生成 10 个测试点，N 在缩数据范围内。
long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand((unsigned)time(0));

    vector<long long> test_cases(10);

    // 1 样例（验证点 E(4)=9）
    test_cases[0] = 4;

    // 2-5 小数据
    for (int i = 1; i < 5; i++) {
        test_cases[i] = rand_ll(1, 20);
    }

    // 6-9 较大数据（缩数据上界 500）
    for (int i = 5; i < 9; i++) {
        test_cases[i] = rand_ll(100, 500);
    }

    // 10 上界
    test_cases[9] = 500;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }
    return 0;
}
