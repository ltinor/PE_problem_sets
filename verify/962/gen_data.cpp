#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand((unsigned)time(0));

    // PE 962 缩数据版：N ≤ 1000，覆盖小样本、中等、边界与最大值
    vector<ll> tc = {3, 10, 20, 50, 100, 200, 500, 1000, 999, 7};

    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32];
        snprintf(fn, sizeof(fn), "data/%02d.in", i + 1);
        ofstream f(fn);
        f << tc[i] << "\n";
        f.close();
        cout << "Generated " << fn << " with N = " << tc[i] << "\n";
    }

    return 0;
}
