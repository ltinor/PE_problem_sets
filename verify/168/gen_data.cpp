#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    
    vector<int> test_cases(10);
    
    test_cases[0] = 2;    // 10 < n < 100, small
    test_cases[1] = 3;
    test_cases[2] = 4;
    test_cases[3] = 5;
    test_cases[4] = 6;
    test_cases[5] = 7;
    test_cases[6] = 8;
    test_cases[7] = 10;
    
    // PE original: D = 100
    test_cases[8] = 100;
    test_cases[9] = 12;
    
    for(int i = 0; i < 10; i++){
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with D = " << test_cases[i] << "\n";
    }
    
    return 0;
}
