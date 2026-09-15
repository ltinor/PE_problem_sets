#include<bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    vector<pair<int,int>> tc = {
        {4,0}, {4,1}, {4,2}, {6,0}, {6,1}, {6,2},
        {8,0}, {8,5}, {10,0}, {10,5}
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i].first << " " << tc[i].second << "\n";
    }
}
