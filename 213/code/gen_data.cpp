#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Pair: {N, R}
    vector<pair<int,int>> tests = {
        {2, 1}, {3, 2}, {4, 3}, {5, 5},
        {6, 10}, {10, 10}, {15, 20}, {20, 30},
        {25, 40}, {30, 50}  // PE answer: 330.721154
    };

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i].first << " " << tests[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with N=" << tests[i].first << " R=" << tests[i].second << "\n";
    }

    return 0;
}
