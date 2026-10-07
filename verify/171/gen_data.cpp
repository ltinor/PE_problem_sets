#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");

    vector<int> test_cases = {
        1,   // D=1: 10^1, small
        2,   // D=2
        3,   // D=3
        4,   // D=4
        5,   // D=5
        6,   // D=6
        10,  // D=10, medium
        15,  // D=15
        20,  // D=20, PE original
        18   // D=18
    };

    for(int i = 0; i < (int)test_cases.size(); i++){
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with D = " << test_cases[i] << "\n";
    }

    return 0;
}
