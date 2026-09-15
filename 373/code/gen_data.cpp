#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    vector<int> tests = {10, 50, 100, 200, 300, 500, 700, 1000, 1200, 1500};
    for (int i = 0; i < 10; i++) {
        string fname = "data/" + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " n=" << tests[i] << "\n";
    }
    return 0;
}
