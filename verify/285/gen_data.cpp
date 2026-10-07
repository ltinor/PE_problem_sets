#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    vector<long long> tests = {1, 2, 5, 10, 50, 100, 500, 1000, 10000, 100000};
    for (int i = 0; i < (int)tests.size(); i++) {
        string fname = string("data/") + (i<9?"0":"") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
    }
    return 0;
}
