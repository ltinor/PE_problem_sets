#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> test_cases(10);

    // 1: Sample from PE original (T=2000000, answer: area 2772 = 36*77)
    test_cases[0] = 2000000;

    // 2-3: Small T
    test_cases[1] = 1;
    test_cases[2] = 18; // 3x2 grid has exactly 18 rectangles

    // 4-6: Medium random
    for (int i = 3; i < 6; i++) {
        test_cases[i] = rand_ll(1000, 100000);
    }

    // 7-9: Large (close to max 10^7)
    test_cases[6] = 10000000;  // max
    test_cases[7] =  9999999;
    test_cases[8] = rand_ll(5000000, 10000000);

    // 10: Random medium-large
    test_cases[9] = rand_ll(100000, 5000000);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with T = " << test_cases[i] << "\n";
    }

    return 0;
}
