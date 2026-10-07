#include <bits/stdc++.h>
using namespace std;

// 生成 10 组测试数据 data/01.in .. data/10.in
// 数据范围 0 <= N <= 20，覆盖样例、边界与随机值。

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> tc(10);

    // 样例（验证点）
    tc[0] = 2;   // C(2)=2
    tc[1] = 10;  // C(10)=1301
    tc[2] = 20;  // C(20)=5895236

    // 边界
    tc[3] = 0;   // C(0)=1
    tc[4] = 1;   // C(1)=1

    // 其余随机（含若干小值便于人工核对）
    for (int i = 5; i < 10; i++) tc[i] = rand_ll(0, 20);

    for (int i = 0; i < 10; i++) {
        string filename = "data/" + string(i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tc[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << tc[i] << "\n";
    }
    return 0;
}
