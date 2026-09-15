#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1-2: small N
    test_cases[0] = 9;    // f(9)=36288
    test_cases[1] = 10;   // f(10)=36288

    // 3-4: medium
    test_cases[2] = 20;   // f(20)=17664
    test_cases[3] = 100;

    // 5-7: large
    test_cases[4] = 1000;
    test_cases[5] = 10000;
    test_cases[6] = 100000;

    // 8-9: very large
    test_cases[7] = 1000000000LL;
    test_cases[8] = 1000000000000LL;  // PE answer: 16576

    // 10: edge
    test_cases[9] = 1;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
