#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    for (int i = 1; i <= 5; i++) {
        string fname = string("data/0") + to_string(i) + ".in";
        ofstream fout(fname);
        fout << i << " 14\n";
        fout.close();
    }
    return 0;
}
