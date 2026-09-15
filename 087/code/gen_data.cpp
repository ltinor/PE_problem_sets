#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1 样例 N=50 → 4
    test_cases[0] = 50;

    // 2-3 小数据
    for (int i = 1; i < 3; i++) {
        test_cases[i] = rand_ll(1, 10000);
    }

    // 4-6 大数据
    for (int i = 3; i < 6; i++) {
        test_cases[i] = rand_ll(40000000, 50000000);
    }

    // 7-8 边界
    test_cases[6] = 1;
    test_cases[7] = 50000000;

    // 9-10 随机
    for (int i = 8; i < 10; i++) {
        test_cases[i] = rand_ll(1, 50000000);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
