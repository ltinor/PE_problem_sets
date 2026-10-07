#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    struct Test { int m, n; long long M; };
    // All m,n in {1,2,3}^2, plus a couple of mod-value checks.
    vector<Test> tests = {
        {1, 1, 100}, {1, 2, 100}, {2, 1, 100}, {2, 2, 100},
        {1, 3, 100}, {3, 1, 100}, {2, 3, 1000000000}, {3, 2, 1000000000},
        {3, 3, 1000000000}, {3, 3, 1000}
    };
    for (int i = 0; i < (int)tests.size(); i++) {
        string fname = string("data/0") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i].m << " " << tests[i].n << " " << tests[i].M << "\n";
        fout.close();
    }
    return 0;
}
