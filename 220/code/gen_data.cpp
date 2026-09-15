#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    
    // Format: n K
    vector<pair<int,ll>> tests(10);
    tests[0] = {0, 1};
    tests[1] = {1, 1};
    tests[2] = {1, 2};
    tests[3] = {2, 3};
    tests[4] = {3, 5};
    tests[5] = {5, 20};
    tests[6] = {10, 500};    // PE example: D_10, after 500 steps → (18,16)
    tests[7] = {10, 1000};
    tests[8] = {15, 20000};
    tests[9] = {50, 1000000000000LL}; // PE original
    
    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i].first << " " << tests[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with n=" << tests[i].first << " K=" << tests[i].second << "\n";
    }
    
    return 0;
}
