#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1 样例：PE 原题
    test_cases[0] = 124;

    // 2-3 小数据
    test_cases[1] = 1;   // 第一个: 27
    test_cases[2] = 10;

    // 4-5 中数据
    test_cases[3] = 50;
    test_cases[4] = 100;

    // 6-7 稍大数据
    test_cases[5] = 200;
    test_cases[6] = 300;

    // 8-9 边界
    test_cases[7] = 2;
    test_cases[8] = 500;

    // 10 随机
    test_cases[9] = rand_ll(10, 400);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
