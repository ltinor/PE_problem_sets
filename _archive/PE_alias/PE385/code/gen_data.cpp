#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));
    vector<ll> tc(10);
    tc[0] = 8;           // sample: ans=72
    tc[1] = 10;          // sample: ans=252
    tc[2] = 5;
    tc[3] = 6;
    tc[4] = 7;
    tc[5] = 9;
    tc[6] = 3;
    tc[7] = 4;
    tc[8] = 11;
    tc[9] = 12;
    for (int i=0; i<10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
