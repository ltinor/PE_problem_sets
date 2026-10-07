#include<bits/stdc++.h>
using namespace std;
typedef long double ld;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct Case {
        int n;
        long long target;
    };
    vector<Case> test_cases(10);

    // 1 样例：PE 原题
    test_cases[0] = {5000, -600000000000LL};

    // 2-3 小数据
    test_cases[1] = {2, 0};
    test_cases[2] = {10, 5000};

    // 4-5 中数据
    test_cases[3] = {100, -100000};
    test_cases[4] = {300, 0}; // s(1) = 0 when n=300? Check: 900-3k average is 0 at k=300

    // s(1) for n=300: 900*300 - 1.5*300*301 = 270000 - 135450 = 134550
    // Let's use different targets
    test_cases[4] = {300, 100000};

    // 6-7 稍大数据
    test_cases[5] = {1000, -10000000};
    test_cases[6] = {2000, -50000000};

    // 8-9 边界
    test_cases[7] = {1, 897}; // s(r) = 897 for any r when n=1 (just k=1, term=897*r^0=897)
    test_cases[8] = {500, -1};

    // 10 随机
    test_cases[9] = {rand_int(1000, 4000), -(long long)rand_int(1000000, 100000000)};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].n << " " << test_cases[i].target << "\n";
        fout.close();
        cout << "Generated " << filename << " with n=" << test_cases[i].n
             << " target=" << test_cases[i].target << "\n";
    }

    return 0;
}
