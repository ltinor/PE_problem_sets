#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data"); srand(time(0));
    vector<ll> tc = {10, 100, 1000, 5, 20, 50, 200, 500, 2000, 5000};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
}
