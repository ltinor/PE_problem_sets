#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> tests(10);
    tests[0] = 1;    // 1st: 1992008
    tests[1] = 2;    // 2nd
    tests[2] = 3;
    tests[3] = 5;
    tests[4] = 10;
    tests[5] = 20;
    tests[6] = 50;
    tests[7] = 100;
    tests[8] = 200;  // PE answer: 229161792008
    tests[9] = 150;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with K = " << tests[i] << "\n";
    }

    return 0;
}
