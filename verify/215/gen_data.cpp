#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // {W, H} pairs
    vector<pair<int,int>> tests = {
        {4, 2},
        {6, 3},
        {9, 3},    // PE example: W(9,3) = 8
        {10, 3},
        {12, 4},
        {16, 5},
        {20, 6},
        {24, 7},
        {28, 8},
        {32, 10}   // PE answer: 806844323190414
    };

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i].first << " " << tests[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with W=" << tests[i].first << " H=" << tests[i].second << "\n";
    }

    return 0;
}
