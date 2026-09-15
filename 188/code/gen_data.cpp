#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    srand(time(0));

    vector<pair<long long, long long>> test_cases(10);

    // 1: sample (original PE)
    test_cases[0] = {1777, 1855};

    // 2-3: small
    test_cases[1] = {2, 3};
    test_cases[2] = {3, 3};

    // 4-6: medium
    test_cases[3] = {10, 10};
    test_cases[4] = {100, 100};
    test_cases[5] = {500, 500};

    // 7: boundary
    test_cases[6] = {2000, 2000};

    // 8-10: random
    test_cases[7] = {rand_ll(2, 200), rand_ll(2, 200)};
    test_cases[8] = {rand_ll(200, 1000), rand_ll(200, 1000)};
    test_cases[9] = {rand_ll(1000, 2000), rand_ll(1000, 2000)};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with A=" << test_cases[i].first << " B=" << test_cases[i].second << "\n";
    }

    return 0;
}
