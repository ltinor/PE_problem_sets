#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 10 test cases for OJ
    // n from 4 to 11, k various
    vector<pair<int,int>> cases = {
        {4, 1},   // sample: DACB / DBAC
        {4, 2},
        {6, 10},  // sample: DFAECB
        {7, 1},
        {8, 5},
        {9, 10},
        {10, 50},
        {10, 100},
        {11, 2011}, // PE answer
        {11, 1}
    };

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i].first << " " << cases[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " n=" << cases[i].first << " k=" << cases[i].second << "\n";
    }
    return 0;
}
