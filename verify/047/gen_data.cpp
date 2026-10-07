#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    srand(time(0));
    
    // 10 test cases: each K value 2-3 times + sample (K=4 is original)
    vector<int> test_cases(10);
    test_cases[0] = 4; // original PE problem (sample)
    test_cases[1] = 1;
    test_cases[2] = 1;
    test_cases[3] = 2;
    test_cases[4] = 2;
    test_cases[5] = 3;
    test_cases[6] = 3;
    test_cases[7] = 4;
    test_cases[8] = 4;
    test_cases[9] = 3;
    
    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K=" << test_cases[i] << "\n";
    }
    
    return 0;
}
