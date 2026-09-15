#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (T=10, answer n=17)
    test_cases[0] = 10;

    // 2-3: small T
    test_cases[1] = 1;
    test_cases[2] = 5;

    // 4-6: medium T
    test_cases[3] = 100;
    test_cases[4] = 1000;
    test_cases[5] = 10000;

    // 7-8: larger T
    test_cases[6] = 100000;
    test_cases[7] = 500000;

    // 9-10: near max
    test_cases[8] = 1000000;
    test_cases[9] = rand_ll(900000, 999999);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with T = " << test_cases[i] << "\n";
    }

    return 0;
}
