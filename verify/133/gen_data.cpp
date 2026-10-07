#include <bits/stdc++.h>
using namespace std;

int rand_ll(int l, int r) { return l + rand() % (r - l + 1); }

int main() {
    system("mkdir -p data");
    srand(time(0));
    // PE answer (M=100000, ans=453647705) verified separately — not in test data
    int cases[] = {100, 200, 500, 1000, 2000, 5000, 10000, 15000, 20000, rand_ll(100, 20000)};
    for (int i = 0; i < 10; i++) {
        string fn = string("data/") + (i<9?"0":"") + to_string(i+1) + ".in";
        ofstream f(fn); f << cases[i] << "\n";
    }
}
