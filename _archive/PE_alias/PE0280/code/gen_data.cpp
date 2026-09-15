#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    vector<int> cases(10);

    // 1-3. small grids (G=1,2,3) — can verify manually or with simpler methods
    cases[0] = 1;
    cases[1] = 2;
    cases[2] = 3;

    // 4. G=4 (medium)
    cases[3] = 4;

    // 5-10. all G=5 (the PE problem) — different random seeds won't matter but just for completeness
    for (int i = 4; i < 10; i++)
        cases[i] = 5;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " G=" << cases[i] << "\n";
    }
    return 0;
}
