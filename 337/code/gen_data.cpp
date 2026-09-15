#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> cases = {
        10,        // sample S(10)=4
        100,       // sample S(100)=482073668
        10000,     // sample S(10000) mod = 73808307
        5000,
        50000,
        500000,
        2000000,
        10000000,
        15000000,
        20000000  // PE answer
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
