#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1-2: small N
    test_cases[0] = 10;
    test_cases[1] = 100;

    // 3-5: medium N
    test_cases[2] = 1000;
    test_cases[3] = 10000;
    test_cases[4] = 50000;

    // 6-8: large N
    test_cases[5] = 100000;
    test_cases[6] = 500000;
    test_cases[7] = 999999;

    // 9-10: PE answer
    test_cases[8] = 999999;
    test_cases[9] = 2; // minimum

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
