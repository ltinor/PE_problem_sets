#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    // 简单版本：小 k,n 测试点（含验证点 C(3,2)）
    vector<pair<int,int>> tc = {
        {2,2}, {2,3}, {3,2}, {3,3}, {4,2}, {3,4}, {2,5}, {5,2}, {4,3}, {2,6}
    };
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tc[i].first << " " << tc[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with k,n = " << tc[i].first << "," << tc[i].second << "\n";
    }
    return 0;
}
