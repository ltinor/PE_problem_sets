#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct TC { ll N; int B; };
    vector<TC> test_cases;

    // 1 样例 (验证点 F(10,4)=5)
    test_cases.push_back({10, 4});

    // 2-3 小数据
    for (int i = 0; i < 2; i++)
        test_cases.push_back({rand_ll(1, 10000), rand() % 40 + 1});

    // 4-6 大数据 (N 接近上界 1e18)
    for (int i = 0; i < 3; i++)
        test_cases.push_back({rand_ll(1000000000000000000LL - 1000000, 1000000000000000000LL), rand() % 40 + 1});

    // 7-8 边界条件
    test_cases.push_back({1, 1});                             // 最小值
    test_cases.push_back({1000000000000000000LL, 40});       // 最大值

    // 9-10 随机数
    for (int i = 0; i < 2; i++)
        test_cases.push_back({rand_ll(1, 1000000000000000000LL), rand() % 40 + 1});

    for (int i = 0; i < (int)test_cases.size(); i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].N << " " << test_cases[i].B << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i].N << ", B = " << test_cases[i].B << "\n";
    }

    return 0;
}
