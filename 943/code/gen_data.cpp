#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    // 简单版本：小 N 测试点（含验证点 T(2,3,10), T(4,2,1e4), T(5,8,1e6)）
    vector<tuple<ll,ll,ll>> tc = {
        {2,3,10}, {4,2,10000}, {5,8,1000000},
        {3,5,100}, {2,5,1000}, {7,3,10000},
        {6,2,50000}, {3,7,100000}, {9,4,1000000}, {2,9,1000000}
    };
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << get<0>(tc[i]) << " " << get<1>(tc[i]) << " " << get<2>(tc[i]) << "\n";
        fout.close();
        cout << "Generated " << fname << "\n";
    }
    return 0;
}
