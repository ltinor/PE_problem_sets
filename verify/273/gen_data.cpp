#include <bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    vector<int> cases = {10, 20, 30, 50, 70, 90, 110, 130, 140, 149};
    for (int i = 0; i < 10; i++) {
        string f = string("data/") + (i<9?"0":"") + to_string(i+1) + ".in";
        ofstream out(f); out << cases[i] << "\n";
    }
    return 0;
}
