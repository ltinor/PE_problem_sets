#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    vector<int> test_cases = {
        10,  // D=10: minimum for pandigital
        11,  // D=11
        12,  // D=12
        13,  // D=13
        14,  // D=14
        15,  // D=15
        20,  // D=20
        25,  // D=25
        30,  // D=30
        40   // D=40, PE original
    };

    for (int i = 0; i < (int)test_cases.size(); i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with D = " << test_cases[i] << "\n";
    }

    return 0;
}
