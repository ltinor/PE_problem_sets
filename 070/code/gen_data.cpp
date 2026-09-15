#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases = {
        100,        // 样例：小范围
        1000,       // 小数据
        10000,      // 小数据  
        100000,     // 中等
        500000,     // 中等
        1000000,    // 较大
        5000000,    // 较大
        9999999,    // 边界
        10000000,   // 最大值 (原题范围)
        rand_int(100, 1000000)  // 随机
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
