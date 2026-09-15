#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));
    vector<ll> tc(10);
    tc[0] = 10000;       // sample: ans=90619
    tc[1] = 100;
    tc[2] = 1000;
    tc[3] = 100000;
    tc[4] = 1000000;
    tc[5] = 10000000;
    tc[6] = 10;
    tc[7] = 50000;
    tc[8] = 500000;
    tc[9] = 100000000;
    for (int i=0; i<10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
