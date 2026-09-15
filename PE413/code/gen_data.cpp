#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data"); srand(time(0));
    vector<ll> tc;
    for (int d = 1; d <= 5; d++) {
        ll pow10 = 1;
        for (int i = 0; i < d; i++) pow10 *= 10;
        tc.push_back(pow10); // F(10^d)
    }
    tc.push_back(100); tc.push_back(1000); tc.push_back(500);
    tc.push_back(10000); tc.push_back(20);
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
}
