#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    srand(time(0));

    vector<long long> test_cases(10);

    // 1: sample
    test_cases[0] = 30;

    // 2-3: small N
    test_cases[1] = 10;
    test_cases[2] = 100;

    // 4-6: large N
    test_cases[3] = 100000;
    test_cases[4] = 10000000;
    test_cases[5] = 50000000;

    // 7: boundary - original PE answer boundary
    test_cases[6] = 100000000;

    // 8-10: random
    test_cases[7] = rand_ll(1000, 10000);
    test_cases[8] = rand_ll(100000, 1000000);
    test_cases[9] = rand_ll(1000000, 10000000);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
