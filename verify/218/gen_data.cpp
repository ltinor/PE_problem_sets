#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    
    vector<ll> tests(10);
    tests[0] = 100;
    tests[1] = 1000;
    tests[2] = 10000;
    tests[3] = 100000;
    tests[4] = 1000000;
    tests[5] = 10000000;
    tests[6] = 100000000;
    tests[7] = 1000000000;
    tests[8] = 10000000000000000LL; // 10^16, PE original
    tests[9] = 5000000000000000LL;  // 5×10^15
    
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with C = " << tests[i] << "\n";
    }
    
    return 0;
}
