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
    test_cases[0] = 75000000;

    // 2-3 小数据
    test_cases[1] = 50;
    test_cases[2] = 200;

    // 4-5 中数据
    test_cases[3] = 1000;
    test_cases[4] = 5000;

    // 6-7 较大数据
    test_cases[5] = 50000;
    test_cases[6] = 500000;

    // 8-9 大数据
    test_cases[7] = 5000000;
    test_cases[8] = 25000000;

    // 10 中等
    test_cases[9] = 100000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
