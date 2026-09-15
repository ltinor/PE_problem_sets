#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data"); srand(time(0));
    vector<ll> tc = {1000, 1000000, 5, 10, 20, 100, 10000, 100000, 5000000, 20000000};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
}
