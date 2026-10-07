#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Each test file contains multiple test cases
    // Format: T on first line, then T lines with N T_threshold
    vector<pair<int, ll>> test_cases;

    // Original PE problem: N=100, T=1000000, answer=4075
    test_cases.push_back({100, 1000000});

    // Small N
    test_cases.push_back({1, 0});
    test_cases.push_back({10, 100});
    test_cases.push_back({23, 1000000});

    // Medium N
    test_cases.push_back({50, 1000000});
    test_cases.push_back({50, 100000000000LL});

    // Large N
    test_cases.push_back({100, 1000});
    test_cases.push_back({100, 1000000000});
    test_cases.push_back({100, 1000000000000LL});

    // Random
    test_cases.push_back({50 + rand() % 51, rand_ll(1, 1000000000000LL)});

    // We'll create 10 separate data files, each with 1 test case
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << "1\n";  // one test case per file
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i].first
             << " T=" << test_cases[i].second << "\n";
    }

    return 0;
}
