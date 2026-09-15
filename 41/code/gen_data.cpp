#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample N=4 -> 4231
    test_cases[0] = 4;

    // 2: N=1 -> no 1-digit pandigital prime? 1 is not prime, so -1
    test_cases[1] = 1;

    // 3: N=2 -> 21? no. actually pandigital 1,2: 21,12 -> neither prime -> -1
    test_cases[2] = 2;

    // 4: N=3 -> check: 321,312,231,213,132,123... none prime? Let's check...
    // 321=3*107, 312 even, 231=3*77, 213=3*71, 132 even, 123=3*41. None prime -> -1
    test_cases[3] = 3;

    // 5: N=5 -> try permutations...
    test_cases[4] = 5;

    // 6-7: random N
    test_cases[5] = 6;
    test_cases[6] = 7;

    // 8-9: random N
    test_cases[7] = 8;
    test_cases[8] = 9;

    // 10: PE original N=7 answer 7652413
    test_cases[9] = 7;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
