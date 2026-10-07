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

    // 1 样例
    test_cases[0] = 6;  // first 6: 6, 42, 120, 156, 420, 630 -> 6th = 630

    // 2-3 小数据
    for (int i = 1; i < 3; i++) {
        test_cases[i] = rand_ll(1, 50);
    }

    // 4-6 中数据
    for (int i = 3; i < 6; i++) {
        test_cases[i] = rand_ll(100, 10000);
    }

    // 7-8 大数据
    test_cases[6] = 150000;  // PE 原题
    test_cases[7] = rand_ll(140000, 149999);

    // 9-10 边界
    test_cases[8] = 1;       // 第1个
    test_cases[9] = 1000;    // 中等

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
