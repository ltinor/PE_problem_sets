#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    vector<string> tc = {
        "3 5 100",
        "5 10 10000",
        "10 20 1000000",
        "PE"
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32];
        sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i] << "\n";
    }
}
