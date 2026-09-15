#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    struct Test { int m; long long n; long long M; };
    vector<Test> tests = {
        {0, 5, 100}, {1, 10, 100}, {2, 7, 100},
        {3, 4, 1000}, {3, 10, 1475789056},
        {0, 0, 100}, {1, 0, 100}, {2, 0, 100}
    };
    
    for (int i = 0; i < (int)tests.size(); i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << tests[i].m << " " << tests[i].n << " " << tests[i].M << "\n";
        fout.close();
    }
    return 0;
}
