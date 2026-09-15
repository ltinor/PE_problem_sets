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
    test_cases[0] = 13195;
    // test_cases[1] = 600851475143;

    // 2-3 小数据 (n < 10000)
    for (int i = 1; i < 3; i++) {
        test_cases[i] = rand_ll(1, 10000);
    }

    // 4-7 随机数 
    for (int i = 3; i < 7; i++) {
        test_cases[i] = rand_ll(2, 1e9);
    }

    // 8-10 边界条件
    test_cases[7] = 2;           // 最小值
    test_cases[8] = 3; 
    test_cases[9] = 1e9; // 最大值

    // // 9-10 随机数
    // for (int i = 8; i < 10; i++) {
    //     test_cases[i] = rand_ll(1, 1000000000000LL);
    // }


    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }

    return 0;
}