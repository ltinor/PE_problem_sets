#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct TestCase { ll N, K, L, R; };
    vector<TestCase> test_cases(10);

    // 1. Very small (brute verifiable)
    test_cases[0] = {20, 5, 3, 13};

    // 2. Small
    test_cases[1] = {30, 10, 3, 13};
    test_cases[2] = {50, 15, 5, 17};

    // 3-5. Medium
    test_cases[3] = {1000, 200, 10, 30};
    test_cases[4] = {5000, 1000, 10, 30};
    test_cases[5] = {10000, 3000, 20, 40};

    // 6-7. Larger primes range
    test_cases[6] = {100000, 10000, 50, 100};
    test_cases[7] = {1000000, 50000, 50, 100};

    // 8-9. PE problem (the actual answer)
    test_cases[8] = {1000000000000000000LL, 1000000000, 1000, 5000};
    test_cases[9] = {1000000000000000000LL, 1000000000, 1000, 5000};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i].N << " " << test_cases[i].K << " " 
             << test_cases[i].L << " " << test_cases[i].R << "\n";
        fout.close();
        cout << "Generated " << fname << "\n";
    }
    return 0;
}
