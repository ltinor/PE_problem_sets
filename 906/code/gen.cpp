#include<bits/stdc++.h>
using namespace std;

// 生成单个随机测试输入（用于 check.sh 对拍）
int main(int argc, char* argv[]) {
    srand((unsigned)time(0));
    int lo = 1, hi = 6;
    if (argc > 1) { string m = argv[1]; if (m == "small") { lo = 1; hi = 5; } else if (m == "large") { lo = 6; hi = 6; } }
    int n = lo + rand() % (hi - lo + 1);
    cout << n << "\n";
    return 0;
}
