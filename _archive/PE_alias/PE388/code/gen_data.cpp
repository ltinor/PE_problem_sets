#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));
    vector<ll> tc(10);
    tc[0] = 100;          // sample
    tc[1] = 10;
    tc[2] = 50;
    tc[3] = 200;
    tc[4] = 500;
    tc[5] = 1000;
    tc[6] = 1;
    tc[7] = 2;
    tc[8] = 20;
    tc[9] = 300;
    for (int i=0; i<10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
