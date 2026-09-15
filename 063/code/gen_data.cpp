#include <bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    for (int i = 1; i <= 10; i++) {
        string fn = string("data/") + (i < 10 ? "0" : "") + to_string(i) + ".in";
        ofstream f(fn);
        f << "0\n";
    }
}
