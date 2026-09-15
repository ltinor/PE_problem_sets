#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    
    vector<int> test_cases(10);
    
    // 1: original PE problem (D=4)
    test_cases[0] = 4;
    
    // 2-3: D=4 additional tests
    test_cases[1] = 4;
    test_cases[2] = 4;
    
    // 4-6: D=5
    test_cases[3] = 5;
    test_cases[4] = 5;
    test_cases[5] = 5;
    
    // 7-9: D=6
    test_cases[6] = 6;
    test_cases[7] = 6;
    test_cases[8] = 6;
    
    // 10: D=4 again
    test_cases[9] = 4;
    
    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with D=" << test_cases[i] << "\n";
    }
    
    return 0;
}
