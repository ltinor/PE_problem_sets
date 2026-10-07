#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1: PE answer (M=1000000, answer=18613426663617118)
    test_cases[0] = 1000000;

    // 2-3: small
    test_cases[1] = 100;
    test_cases[2] = 500;

    // 4-6: medium
    test_cases[3] = 1000;
    test_cases[4] = 10000;
    test_cases[5] = 50000;

    // 7-8: larger
    test_cases[6] = 100000;
    test_cases[7] = 500000;

    // 9: near max
    test_cases[8] = 900000;

    // 10: random
    test_cases[9] = rand_ll(100, 999999);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}
