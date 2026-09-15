#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    vector<string> tc = {
        "1",
        "2",
        "3",
        "4",
        "5",
        "11",
        "100",
        "1000",
        "10000",
        "PE"
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32];
        sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i] << "\n";
    }
}
