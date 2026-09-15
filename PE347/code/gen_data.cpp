#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    vector<ll> tc = {
        10,
        100,          // sample: S(100)=2262
        500,
        1000,
        100000,
        1000000,
        5000000,
        10000000      // PE answer
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
