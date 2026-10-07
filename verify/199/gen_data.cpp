#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> tests(10);
    tests[0] = 3;   // sample: 0.06790342
    tests[1] = 0;
    tests[2] = 1;
    tests[3] = 2;
    tests[4] = 4;
    tests[5] = 5;
    tests[6] = 6;
    tests[7] = 8;
    tests[8] = 10;  // PE answer: 0.00396087
    tests[9] = 10;  // duplicate

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with K = " << tests[i] << "\n";
    }

    return 0;
}
