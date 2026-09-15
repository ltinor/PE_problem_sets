#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> cases(10);
    cases[0] = 100;      // sample: P=100, answer=5482
    cases[1] = 10;       // small
    cases[2] = 50;
    cases[3] = 200;
    cases[4] = 500;
    cases[5] = 1000;
    cases[6] = 10000;
    cases[7] = 100000;
    cases[8] = 500000;
    cases[9] = 1000000;  // PE problem

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " P=" << cases[i] << "\n";
    }
    return 0;
}
