#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    // 10 test cases (a, b) pairs
    vector<pair<long long, long long>> tests(10);

    tests[0] = {1, 2};     // P(m) < 1/2 → should be small
    tests[1] = {1, 3};     // P(m) < 1/3
    tests[2] = {1, 5};
    tests[3] = {1, 10};
    tests[4] = {1, 20};
    tests[5] = {1, 100};
    tests[6] = {1, 500};
    tests[7] = {1, 1000};
    tests[8] = {1, 10000};
    tests[9] = {1, 12345}; // PE answer

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i].first << " " << tests[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with a=" << tests[i].first << " b=" << tests[i].second << "\n";
    }

    return 0;
}
