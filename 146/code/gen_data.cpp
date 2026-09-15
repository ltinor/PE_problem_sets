#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1: PE sample (M=1000000, answer should be 1242490)
    test_cases[0] = 1000000;

    // 2-3: small M (< 10000)
    test_cases[1] = 100;
    test_cases[2] = 1000;

    // 4-5: medium M
    test_cases[3] = 10000;
    test_cases[4] = 20000;

    // 6-7: larger M
    test_cases[5] = 100000;
    test_cases[6] = 500000;

    // 8-9: near max
    test_cases[7] = 2000000;
    test_cases[8] = 10000000;

    // 10: PE answer (M=150000000, answer=676333270)
    test_cases[9] = 150000000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M=" << test_cases[i] << "\n";
    }

    return 0;
}
