#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1: PE answer (R=1000000000, answer=2129968654)
    test_cases[0] = 1000000000;

    // 2-3: small R
    test_cases[1] = 1;
    test_cases[2] = 10;

    // 4-5: medium R
    test_cases[3] = 100;
    test_cases[4] = 1000;

    // 6-7: larger R
    test_cases[5] = 10000;
    test_cases[6] = 100000;

    // 8-10: various R
    test_cases[7] = 1000000;
    test_cases[8] = 10000000;
    test_cases[9] = 5764801; // 7^8, interesting power of 7

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with R=" << test_cases[i] << "\n";
    }

    return 0;
}
