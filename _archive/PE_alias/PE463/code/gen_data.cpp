#include<bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    vector<ll> tc = {3, 5, 8, 10, 50, 100, 1000, 10000, 100000, 1000000};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
}
