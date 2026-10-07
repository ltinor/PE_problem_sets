#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");

    vector<ll> tests(10);
    tests[0] = 4;      // N(4)=24
    tests[1] = 8;      // N(8)=100
    tests[2] = 12;
    tests[3] = 20;
    tests[4] = 50;
    tests[5] = 100;
    tests[6] = 200;
    tests[7] = 500;
    tests[8] = 1000;
    tests[9] = 2000;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with r = " << tests[i] << "\n";
    }

    return 0;
}
