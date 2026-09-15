#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    vector<tuple<ll,ll,ll,ll>> tc = {
        {10, 100, 1, 1000000007},     // sample: f(10,100,1)=91
        {10, 100, 2, 1000000007},     // sample: f(10,100,2)=327
        {10, 100, 3, 1000000007},     // sample: f(10,100,3)=1135
        {10, 100, 1000, 104060401},   // sample: f(10,100,1000) mod 101^4 = 3286053
        {1, 20, 1, 1000000007},
        {5, 50, 2, 1000000007},
        {1, 100, 3, 1000000007},
        {100, 1000, 2, 1000000007},
        {1000, 100000, 2, 1000000007},
        {1000000, 1000000000000LL, 1000000000000000000LL, 104060401} // PE350: G=10^6, L=10^12, N=10^18
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        auto [G, L, N, M] = tc[i];
        ofstream f(fn); f << G << " " << L << " " << N << " " << M << "\n";
    }
    return 0;
}
