#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct Case { ll N, K; };
    vector<Case> test_cases(10);

    // 1 样例：PE 原题
    test_cases[0] = {20000000, 15000000};

    // 2-3 小数据
    test_cases[1] = {10, 5};
    test_cases[2] = {20, 10};

    // 4-5 中数据
    test_cases[3] = {100, 50};
    test_cases[4] = {1000, 300};

    // 6-7 稍大数据
    test_cases[5] = {100000, 50000};
    test_cases[6] = {1000000, 300000};

    // 8-9 边界/特殊
    test_cases[7] = {2, 1};
    test_cases[8] = {5000000, 2500000};

    // 10 随机
    test_cases[9] = {rand_ll(100000, 10000000), 0};
    test_cases[9].K = rand_ll(1, test_cases[9].N - 1);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].N << " " << test_cases[i].K << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i].N
             << " K=" << test_cases[i].K << "\n";
    }

    return 0;
}
