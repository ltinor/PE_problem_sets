#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    vector<int> tests(10);
    tests[0] = 1;
    tests[1] = 2;
    tests[2] = 3;
    tests[3] = 4;
    tests[4] = 5;
    tests[5] = 6;  // PE answer 15964587728784
    tests[6] = 7;
    tests[7] = 6;
    tests[8] = 5;
    tests[9] = 4;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with k = " << tests[i] << "\n";
    }

    return 0;
}
