#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<long long, long long>> cases = {
        {3, 1000},       // C(3)=8 mod 1000 = 8
        {5, 100000},     // small
        {10, 100000000}, // C(10) mod 1e8
        {3, 1000000000},
        {6, 1000000},
        {7, 10000000},
        {8, 100000000},
        {9, 100000000},
        {12, 100000000},
        {15, 100000000}
    };

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i].first << " " << cases[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " n=" << cases[i].first << " M=" << cases[i].second << "\n";
    }
    return 0;
}
