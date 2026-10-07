#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample - N=2, sqrt(2) first 100 digits sum = 475
    test_cases[0] = 2;

    // 2-3: small N
    test_cases[1] = rand_int(3, 10);
    test_cases[2] = rand_int(5, 15);

    // 4-6: medium N
    test_cases[3] = rand_int(20, 40);
    test_cases[4] = rand_int(40, 60);
    test_cases[5] = rand_int(60, 80);

    // 7: minimum boundary
    test_cases[6] = 2;

    // 8: maximum boundary
    test_cases[7] = 100;

    // 9-10: random
    test_cases[8] = rand_int(50, 90);
    test_cases[9] = rand_int(30, 99);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
