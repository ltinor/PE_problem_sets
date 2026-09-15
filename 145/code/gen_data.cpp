#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    vector<int> test_cases(10);

    // 1: sample from problem — D=3 (below 1000 => 120)
    test_cases[0] = 3;

    // 2-3: very small D
    test_cases[1] = 1;
    test_cases[2] = 2;

    // 4-5: small D
    test_cases[3] = 4;
    test_cases[4] = 5;

    // 6-7: medium D
    test_cases[5] = 6;
    test_cases[6] = 7;

    // 8: original problem bound
    test_cases[7] = 9;

    // 9-10: remaining
    test_cases[8] = 8;
    test_cases[9] = 5; // repeat for more coverage

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with D = " << test_cases[i] << "\n";
    }

    return 0;
}
