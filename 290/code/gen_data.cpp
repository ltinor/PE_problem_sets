#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    struct Test { long long E, k; };
    vector<Test> tests = {{1,2},{2,3},{3,2},{4,5},{18,137}};
    for (int i = 0; i < (int)tests.size(); i++) {
        string fname = string("data/0") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << tests[i].E << " " << tests[i].k << "\n";
        fout.close();
    }
    return 0;
}
