#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));
    vector<ll> tc(10);
    tc[0] = 45;          // PE answer: 3354706415856372783
    tc[1] = 5;
    tc[2] = 10;
    tc[3] = 15;
    tc[4] = 20;
    tc[5] = 25;
    tc[6] = 2;
    tc[7] = 30;
    tc[8] = 35;
    tc[9] = 40;
    for (int i=0; i<10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
