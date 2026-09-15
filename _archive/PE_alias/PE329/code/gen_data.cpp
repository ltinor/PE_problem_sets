#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    vector<pair<ll,string>> tc = {
        {5, "PP"},
        {5, "PN"},
        {5, "NP"},
        {10, "PPP"},
        {10, "NPN"},
        {10, "PNP"},
        {20, "PPNN"},
        {20, "NPNP"},
        {30, "PPNPN"},
        {500, "PPPPNNPPPNPPNPN"}  // Original PE problem
    };
    for (int i=0; i<(int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i].first << " " << tc[i].second << "\n";
    }
    return 0;
}
