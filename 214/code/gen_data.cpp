#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // {N, L} pairs
    vector<pair<int,int>> tests = {
        {100, 4},
        {500, 6},
        {1000, 7},
        {5000, 8},
        {10000, 9},
        {50000, 10},
        {100000, 11},
        {500000, 13},
        {1000000, 14},
        {10000000, 20}  // PE: N=40M, L=25 → 1677366278943
    };

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i].first << " " << tests[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with N=" << tests[i].first << " L=" << tests[i].second << "\n";
    }

    return 0;
}
