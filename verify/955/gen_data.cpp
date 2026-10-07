#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1 样例
    test_cases[0] = 10;

    // 2-3 小数据 (k <= 5)
    for (int i = 1; i < 3; i++) {
        test_cases[i] = rand_ll(1, 5);
    }

    // 4-5 中等数据 (k <= 12)
    for (int i = 3; i < 5; i++) {
        test_cases[i] = rand_ll(6, 12);
    }

    // 6 边界：最小值
    test_cases[5] = 1;

    // 7 边界：最大值
    test_cases[6] = 20;

    // 8-10 随机数 (k <= 20)
    for (int i = 7; i < 10; i++) {
        test_cases[i] = rand_ll(1, 20);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with k = " << test_cases[i] << "\n";
    }

    return 0;
}
