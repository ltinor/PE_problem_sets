#include <bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    // Generate 10 test cases for K=3..6
    for (int K = 3; K <= 6; K++) {
        string fn = string("data/0") + to_string(K - 2) + ".in";
        ofstream f(fn);
        f << K << "\n";
    }
    for (int id = 5; id <= 10; id++) {
        string fn = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream f(fn);
        f << "3\n";
    }
}
