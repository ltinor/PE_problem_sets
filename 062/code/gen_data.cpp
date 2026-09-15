#include <bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    for (int K = 2; K <= 5; K++) {
        string fn = string("data/0") + to_string(K - 1) + ".in";
        ofstream f(fn);
        f << K << "\n";
    }
    for (int id = 5; id <= 10; id++) {
        string fn = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream f(fn);
        f << "2\n";
    }
}
