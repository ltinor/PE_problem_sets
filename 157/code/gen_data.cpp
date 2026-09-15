#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: N=1 (sample)
    test_cases[0] = 1;

    // 2-4: small N
    test_cases[1] = 2;
    test_cases[2] = 3;
    test_cases[3] = 4;

    // 5-7: medium N
    test_cases[4] = 5;
    test_cases[5] = 6;
    test_cases[6] = 7;

    // 8-9: large N
    test_cases[7] = 8;
    test_cases[8] = 9;

    // 10: N=9 (PE answer)
    test_cases[9] = 9;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
