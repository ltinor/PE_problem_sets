#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    vector<ll> tc = {
        10,
        100,
        500,
        1000,
        5000,
        10000,
        20000,
        100000,
        1000000,
        1000000000000000000LL // PE answer: 10^18
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
