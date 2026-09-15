#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    vector<pair<ll,ll>> tc = {
        {100, 6},       // small
        {100, 12},      // B(L)=12 (√21 etc)
        {1000, 6},      // medium
        {1000, 12},
        {10000, 6},
        {10000, 12},
        {100000, 6},
        {100000, 18},
        {1000000, 6},
        {500000000000LL, 450}  // PE354: LIMIT=5e11, TARGET=450
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; snprintf(fn, 32, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i].first << " " << tc[i].second << "\n";
    }
    return 0;
}
