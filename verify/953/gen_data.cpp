#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * (ll)rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand((unsigned)time(0));

    vector<ll> test_cases(10);

    // 1-2 样例（题目给定 S(10)=14, S(100)=455）
    test_cases[0] = 10;
    test_cases[1] = 100;

    // 3-4 边界 / 验证点
    test_cases[2] = 1;     // S(1) = 1
    test_cases[3] = 70;    // 70 = 2*5*7，先手必败的验证点

    // 5-6 小数据
    test_cases[4] = rand_ll(2, 10000);
    test_cases[5] = rand_ll(10000, 1000000);

    // 7-8 大数据
    test_cases[6] = rand_ll(1000000, 10000000);
    test_cases[7] = rand_ll(1000000, 10000000);

    // 9 最大边界，10 随机
    test_cases[8] = 10000000LL;
    test_cases[9] = rand_ll(1, 10000000LL);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
