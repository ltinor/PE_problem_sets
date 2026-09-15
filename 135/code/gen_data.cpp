#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,int>> test_cases(10);

    // 1: PE answer (M=1000000, K=10, answer=4989)
    test_cases[0] = {1000000, 10};

    // 2-3: small
    test_cases[1] = {100, 2};
    test_cases[2] = {500, 3};

    // 4-6: medium
    test_cases[3] = {1000, 5};
    test_cases[4] = {10000, 8};
    test_cases[5] = {50000, 10};

    // 7-8: larger
    test_cases[6] = {100000, 12};
    test_cases[7] = {500000, 8};

    // 9: another K
    test_cases[8] = {1000000, 5};

    // 10: random
    test_cases[9] = {(int)rand_ll(100, 500000), (int)rand_ll(1, 15)};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with M=" << test_cases[i].first << " K=" << test_cases[i].second << "\n";
    }

    return 0;
}
