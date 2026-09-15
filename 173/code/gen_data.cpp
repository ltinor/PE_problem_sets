#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");

    vector<int> test_cases = {
        8,      // N=8: only 3x3 with 1x1 hole
        32,     // N=32: two different laminae
        100,    // N=100: 41 laminae
        500,
        1000,
        5000,
        10000,
        100000,
        500000,
        1000000 // PE original
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
