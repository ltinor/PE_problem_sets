#include <bits/stdc++.h>
using namespace std;

// PE 957 简单版本数据生成器：n ∈ [1,4]
int main() {
    system("mkdir -p data");
    vector<int> tc = {1, 2, 1, 2, 3, 3, 4, 4, 3, 4};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32];
        sprintf(fn, "data/%02d.in", i + 1);
        ofstream f(fn);
        f << tc[i] << "\n";
        f.close();
        cout << "Generated " << fn << " with n = " << tc[i] << "\n";
    }
    return 0;
}
