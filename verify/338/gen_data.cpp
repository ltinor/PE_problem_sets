#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> cases = {
        10,       // sample G(10)=55
        1000,     // sample G(1000)=971745
        5000,
        10000,
        20000,
        50000,
        100000,   // sample G(100000)=9992617687
        5000,
        15000,
        80000
    };

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << cases[i] << "\n";
    }
    return 0;
}
