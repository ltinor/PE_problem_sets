#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE answer (K=12, sum=1118049290473932)
    test_cases[0] = 12;

    // 2-4: small K
    test_cases[1] = 1;
    test_cases[2] = 2;
    test_cases[3] = 3;

    // 5-7: medium K
    test_cases[4] = 4;
    test_cases[5] = 5;
    test_cases[6] = 7;

    // 8-10: larger K
    test_cases[7] = 9;
    test_cases[8] = 10;
    test_cases[9] = 11;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K=" << test_cases[i] << "\n";
    }

    return 0;
}
