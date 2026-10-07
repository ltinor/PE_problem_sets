#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    // 简单版本：小 q 测试点（含验证点 R(5), R(17)）
    vector<ll> tc = {5, 17, 2, 3, 4, 7, 11, 13, 19, 23};
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tc[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with q = " << tc[i] << "\n";
    }
    return 0;
}
