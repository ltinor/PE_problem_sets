#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));
    vector<ll> tc = {8, 100, 1, 2, 3, 10, 20, 50, 30, 200};
    for (int i=0; i<(int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
