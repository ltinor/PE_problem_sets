#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(){
    system("mkdir -p data");
    srand(time(0));

    // 10个测试样例
    vector<int> test_cases = {
        10,       // 样例
        20,       // 小数据
        100,      // 小数据
        1000,     // 中等
        10000,    // 中等
        100000,   // 较大
        500000,   // 较大
        999999,   // 边界
        1000000,  // 最大值
        rand_int(1, 1000000)  // 随机
    };

    for(int i = 0; i < 10; i++){
        string fn = string("data/") + (i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream fout(fn);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fn << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
