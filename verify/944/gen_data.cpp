#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    // 简单版本：小 n 测试点（含验证点 S(10)=4927）
    vector<ll> tc = {10, 1, 2, 3, 4, 5, 8, 12, 15, 16};
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tc[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with n = " << tc[i] << "\n";
    }
    return 0;
}
