#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    
    vector<ll> tests(10);
    tests[0] = 1;
    tests[1] = 2;
    tests[2] = 5;
    tests[3] = 6;      // Cost(6) = 35 (from problem statement)
    tests[4] = 10;
    tests[5] = 100;
    tests[6] = 1000;
    tests[7] = 100000;
    tests[8] = 1000000;
    tests[9] = 1000000000;  // PE original
    
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << tests[i] << "\n";
    }
    
    return 0;
}
