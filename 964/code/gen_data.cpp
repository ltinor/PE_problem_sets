#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * (ll)rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand((unsigned)time(0));

    vector<ll> tc(10);
    // 1 样例 (P(3) 验证点)
    tc[0] = 3;
    // 2-3 小数据
    tc[1] = 1;
    tc[2] = 2;
    // 4 小数据 (T=7, k=4)
    tc[3] = 4;
    // 5-8 大 k
    tc[4] = 5;
    tc[5] = 6;
    tc[6] = 7;
    tc[7] = 7;
    // 9-10 随机
    tc[8] = rand_ll(1, 7);
    tc[9] = rand_ll(1, 7);

    for (int i = 0; i < 10; ++i) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tc[i] << "\n";
        cout << "Generated " << fname << " with k = " << tc[i] << "\n";
    }
    return 0;
}
