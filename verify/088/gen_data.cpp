#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1 样例 Kmax=6 → 30
    test_cases[0] = 6;

    // 2 样例 Kmax=12 → 61
    test_cases[1] = 12;

    // 3-4 小数据
    for (int i = 2; i < 4; i++) {
        test_cases[i] = rand_ll(2, 50);
    }

    // 5-7 大数据
    for (int i = 4; i < 7; i++) {
        test_cases[i] = rand_ll(10000, 12000);
    }

    // 8 边界
    test_cases[7] = 2;
    test_cases[8] = 12000;

    // 9-10 随机
    for (int i = 8; i < 10; i++) {
        test_cases[i] = rand_ll(2, 12000);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with Kmax = " << test_cases[i] << "\n";
    }

    return 0;
}
