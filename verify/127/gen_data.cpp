#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (c < 1000, answer = 12523)
    test_cases[0] = 1000;

    // 2-3: small M
    test_cases[1] = 100;
    test_cases[2] = 500;

    // 4-6: medium M
    test_cases[3] = 2000;
    test_cases[4] = 5000;
    test_cases[5] = 10000;

    // 7-8: larger M
    test_cases[6] = 30000;
    test_cases[7] = 60000;

    // 9-10: near max
    test_cases[8] = 120000;
    test_cases[9] = rand_ll(100000, 119999);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}
