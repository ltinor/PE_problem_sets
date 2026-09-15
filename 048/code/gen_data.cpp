#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    system("mkdir -p data");
    srand(time(0));
    
    vector<ll> test_cases(10);
    
    // 1: original PE problem
    test_cases[0] = 1000;
    
    // 2: sample (N=10)
    test_cases[1] = 10;
    
    // 3-4: small
    test_cases[2] = 1;
    test_cases[3] = 5;
    
    // 5-7: medium-large
    test_cases[4] = 100;
    test_cases[5] = 500;
    test_cases[6] = 10000;
    
    // 8-9: large / boundary
    test_cases[7] = 100000;
    test_cases[8] = 1000000;
    
    // 10: random
    test_cases[9] = 2023;
    
    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i] << "\n";
    }
    
    return 0;
}
