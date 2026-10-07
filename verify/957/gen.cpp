#include <bits/stdc++.h>
using namespace std;

// PE 957 简单版本随机数据生成器：随机 n ∈ [1,4]
int main(int argc, char* argv[]) {
    srand((unsigned)time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    int n = rand() % 4 + 1;   // 1..4
    cout << n << "\n";
    return 0;
}
