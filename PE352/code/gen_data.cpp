#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    vector<pair<int,double>> tc = {
        {25, 0.02},   // PE example: T(25,0.02)=4.155452
        {25, 0.10},   // PE example: T(25,0.10)=12.702124
        {10, 0.05},   // small
        {50, 0.02},   // medium
        {100, 0.05},  // medium
        {200, 0.10},  // medium-large
        {500, 0.01},  // large
        {500, 0.30},  // large with high p
        {1000, 0.02}, // large
        {2000, 0.05}  // very large
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; snprintf(fn, 32, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i].first << " " << fixed << setprecision(2) << tc[i].second << "\n";
    }
    return 0;
}
