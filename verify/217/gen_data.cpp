#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    vector<int> tests(10);
    tests[0] = 1;    // T(1) = 45
    tests[1] = 2;    // T(2) = 540
    tests[2] = 3;
    tests[3] = 4;
    tests[4] = 5;    // T(5) = 334795890
    tests[5] = 6;
    tests[6] = 8;
    tests[7] = 10;
    tests[8] = 15;
    tests[9] = 47;   // PE original: 6273134
    
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with n = " << tests[i] << "\n";
    }
    
    return 0;
}
