#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    vector<int> tests(10);
    tests[0] = 2;
    tests[1] = 10;
    tests[2] = 100;
    tests[3] = 1000;
    tests[4] = 10000;       // PE says 2202 for n≤10000
    tests[5] = 50000;
    tests[6] = 100000;
    tests[7] = 500000;
    tests[8] = 50000000;    // PE original: 5437849
    tests[9] = 1000000;
    
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << tests[i] << "\n";
    }
    
    return 0;
}
