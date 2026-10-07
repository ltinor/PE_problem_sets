#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    struct Test { int N, S; double p; };
    vector<Test> tests = {
        {3, 1, 0.5}, {5, 2, 0.3}, {10, 5, 0.1}, {20, 10, 0.05}, {50, 20, 0.02}
    };
    for (int i = 0; i < (int)tests.size(); i++) {
        string fname = string("data/0") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << tests[i].N << " " << tests[i].S << " " << fixed << setprecision(10) << tests[i].p << "\n";
        fout.close();
    }
    return 0;
}
