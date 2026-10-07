#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    srand(time(0));
    
    vector<int> test_cases(10);
    
    // 1: original PE problem (N=1000000)
    test_cases[0] = 1000000;
    
    // 2: sample from problem (N=100)
    test_cases[1] = 100;
    
    // 3: sample from problem (N=1000)
    test_cases[2] = 1000;
    
    // 4-5: small
    test_cases[3] = 10;
    test_cases[4] = 50;
    
    // 6-8: medium
    test_cases[5] = 5000;
    test_cases[6] = 10000;
    test_cases[7] = 50000;
    
    // 9-10: large
    test_cases[8] = 100000;
    test_cases[9] = 500000;
    
    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i] << "\n";
    }
    
    return 0;
}
