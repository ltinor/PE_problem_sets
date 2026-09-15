#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1: PE sample (K=2000, answer M=100)
    test_cases[0] = 2000;

    // 2: Small K
    test_cases[1] = 1;
    test_cases[2] = 5;
    test_cases[3] = 10;

    // 4-6: Medium random
    for (int i = 4; i < 7; i++) {
        test_cases[i] = rand_ll(100, 10000);
    }

    // 7-8: Large
    test_cases[7] = 1000000;  // PE original target
    test_cases[8] =  500000;

    // 9-10: Boundary/random
    test_cases[9] = rand_ll(100000, 1000000);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
