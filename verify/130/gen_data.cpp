#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (first 5 composites: 91,259,451,481,703, sum=1985)
    test_cases[0] = 5;

    // 2-3: small K
    test_cases[1] = 1;
    test_cases[2] = 3;

    // 4-6: medium K
    test_cases[3] = 10;
    test_cases[4] = 15;
    test_cases[5] = 20;

    // 7-8: larger K
    test_cases[6] = 22;
    test_cases[7] = 24;

    // 9-10: near max
    test_cases[8] = 25;
    test_cases[9] = rand_ll(5, 24);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
