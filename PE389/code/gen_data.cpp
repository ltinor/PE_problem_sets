#include<bits/stdc++.h>
using namespace std;

// PE389 always computes variance - input is ignored
int main() {
    system("mkdir -p data");
    vector<int> tc(10, 0); // placeholder inputs
    for (int i=0; i<10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << "0\n";
    }
    return 0;
}
