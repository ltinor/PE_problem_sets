#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,ll>> test_cases(10);

    // 1. Sample: T(4)=8
    test_cases[0] = {4, 1000000007};

    // 2-3. Very small (brute verifiable)
    test_cases[1] = {1, 1000000007};
    test_cases[2] = {3, 1000000007};

    // 4-5. Small
    test_cases[3] = {5, 1000000007};
    test_cases[4] = {7, 1000000007};

    // 6-7. Verify T(10)=61632
    test_cases[5] = {10, 1000000007};
    test_cases[6] = {10, 1000000007}; // duplicate for PE verification

    // 8-9. Medium
    test_cases[7] = {100, 1000000007};
    test_cases[8] = {1000, 100000007};
    test_cases[9] = {1000000, 100000007}; // PE problem

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with N=" << test_cases[i].first 
             << " M=" << test_cases[i].second << "\n";
    }
    return 0;
}
