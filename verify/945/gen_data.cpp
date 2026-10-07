#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    // 简单版本：小 N 测试点（含验证点 F(10)=21）
    vector<ll> tc = {10, 0, 1, 2, 3, 5, 8, 12, 20, 5000};
    for (int i = 0; i < (int)tc.size(); i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tc[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << tc[i] << "\n";
    }
    return 0;
}
