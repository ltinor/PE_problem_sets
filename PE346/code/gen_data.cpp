#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    vector<ll> tc = {
        10,           // sample
        50,           // sample: 8 strong repunits < 50
        1000,         // sample: sum = 15864
        100,
        500,
        2000,
        100000,
        1000000,
        100000000,
        1000000000000LL  // PE answer
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
