#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    
    vector<string> test_cases = {
        "1",
        "10",
        "100",
        "1000",
        "10000",
        "100000",
        "1000000",
        "123456789012345",           // 15-digit test
        "10000000000000000000000000", // 10^25 (PE original)
        "9999999999999999999999999"   // 10^25 - 1
    };
    
    for(int i = 0; i < (int)test_cases.size(); i++){
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << test_cases[i] << "\n";
    }
    
    return 0;
}
