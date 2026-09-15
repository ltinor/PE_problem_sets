#include <bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    for (int id = 1; id <= 10; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream(fname) << "0\n";
    }
}
