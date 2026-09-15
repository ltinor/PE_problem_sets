#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    srand(time(0));

    vector<pair<int,int>> test_cases(10);

    // 1: sample (original PE answer)
    test_cases[0] = {99, 524287};

    // 2-3: small P, random T
    test_cases[1] = {30, 100};
    test_cases[2] = {50, 500000};

    // 4-6: large P, PM
    test_cases[3] = {95, 524287};
    test_cases[4] = {98, 524287};
    test_cases[5] = {100, 524287};

    // 7-8: boundary
    test_cases[6] = {1, 0};
    test_cases[7] = {50, 0};

    // 9-10: random
    test_cases[8] = {60, rand_ll(100000, 900000)};
    test_cases[9] = {80, rand_ll(100000, 900000)};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with P=" << test_cases[i].first << " T=" << test_cases[i].second << "\n";
    }

    return 0;
}
