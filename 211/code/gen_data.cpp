#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> tests = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000};
    // Note: PE answer for N=64000000 is 1922364685 but N≤10^7 for OJ

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << tests[i] << "\n";
    }

    return 0;
}
