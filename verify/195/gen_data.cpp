#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE answer (N=1053779, answer=75085391)
    test_cases[0] = 1053779;

    // 2-3: sample cases from problem statement
    test_cases[1] = 100;    // T(100)=1234
    test_cases[2] = 1000;   // T(1000)=22767

    // 4-5: small for brute verification
    test_cases[3] = 10;
    test_cases[4] = 50;

    // 6-8: medium
    test_cases[5] = 500;
    test_cases[6] = 5000;
    test_cases[7] = 20000;

    // 9: another medium
    test_cases[8] = 10000;  // T(10000)=359912

    // 10: random large
    test_cases[9] = 50000 + rand() % 500000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i] << "\n";
    }

    return 0;
}
