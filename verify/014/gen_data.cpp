#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1-2 样例和小数据
    test_cases[0] = 14;      // 样例: 13以内, 13产生最长链(10项)
    test_cases[1] = 100;     // 小数据

    // 3-5 中等数据
    for (int i = 2; i < 5; i++) {
        test_cases[i] = rand_ll(1000, 100000);
    }

    // 6-8 大数据
    for (int i = 5; i < 8; i++) {
        test_cases[i] = rand_ll(100000, 1000000);
    }

    // 9-10 边界
    test_cases[8] = 2;           // 最小值(N>1)
    test_cases[9] = 5000000;     // 上界

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
