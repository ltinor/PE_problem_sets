#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    vector<ll> tc = {
        5,       // H(5) = 30
        10,      // H(10) = 138
        100,     // H(100) = ?
        1000,    // H(1000) = 1177848
        5000,    // medium
        10000,   // medium-large
        50000,   // large
        100000,  // larger
        500000,  // very large
        1000000  // 1e6
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
