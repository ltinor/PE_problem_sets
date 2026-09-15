#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1 样例：PE 原题
    test_cases[0] = 999966663333LL;

    // 2-3 小数据
    test_cases[1] = 15;
    test_cases[2] = 50;

    // 4-5 中数据
    test_cases[3] = 100;
    test_cases[4] = 1000;

    // 6-7 稍大数据
    test_cases[5] = 100000;
    test_cases[6] = 10000000;

    // 8 边界
    test_cases[7] = 1000000000LL;

    // 9-10 随机大数据
    test_cases[8] = rand_ll(100000000000LL, 500000000000LL);
    test_cases[9] = 1000000000000LL;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
