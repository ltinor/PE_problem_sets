#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 简单版本：只生成小 k 的测试点（缩数据）
    vector<ll> tc = {2, 3, 4, 5, 6, 7, 8, 10, 12, 15};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tc[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with k = " << tc[i] << "\n";
    }
    return 0;
}
