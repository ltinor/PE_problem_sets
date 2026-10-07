#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    // p, q, e
    vector<tuple<int,int,int>> tests = {{3,5,4},{3,10,4},{5,3,3},{7,5,3},{61,10000000,10}};
    for (int i = 0; i < (int)tests.size(); i++) {
        string fname = string("data/0") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << get<0>(tests[i]) << " " << get<1>(tests[i]) << " " << get<2>(tests[i]) << "\n";
        fout.close();
    }
    return 0;
}
