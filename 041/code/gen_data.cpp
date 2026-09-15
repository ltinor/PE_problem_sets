#include <bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    for (int id = 1; id <= 9; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream fout(fname);
        fout << id << "\n";
        fout.close();
    }
    // 10th: N=0 (edge)
    ofstream("data/10.in") << "0\n";
}
