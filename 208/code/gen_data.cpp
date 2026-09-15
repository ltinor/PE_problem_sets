#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    vector<int> tests(10);
    tests[0] = 5;
    tests[1] = 10;
    tests[2] = 15;
    tests[3] = 20;
    tests[4] = 25;
    tests[5] = 30;
    tests[6] = 35;
    tests[7] = 40;
    tests[8] = 70;  // PE answer
    tests[9] = 50;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with n = " << tests[i] << "\n";
    }

    return 0;
}
