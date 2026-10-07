#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");

    // PE 961 缩数据版：N <= 1e6，覆盖验证点、小样本、中等、边界与最大值
    vector<ll> tc = {100, 10000, 10, 1000, 5000, 100000, 999999, 1000000, 12345, 1};

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
