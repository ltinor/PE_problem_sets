#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Format: k n
    vector<pair<int,int>> test_cases(10);

    // 1: PE answer check (k=20000, n=1000000, answer=0.7311720251)
    test_cases[0] = {20000, 1000000};

    // 2-3: sample / very small
    test_cases[1] = {3, 7};
    test_cases[2] = {20, 100};

    // 4-6: small
    test_cases[3] = {5, 10};
    test_cases[4] = {10, 20};
    test_cases[5] = {15, 50};

    // 7-8: medium
    test_cases[6] = {100, 1000};
    test_cases[7] = {500, 5000};

    // 9-10: larger
    test_cases[8] = {2000, 100000};
    test_cases[9] = {10000, 500000};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with k=" << test_cases[i].first
             << " n=" << test_cases[i].second << "\n";
    }

    return 0;
}
