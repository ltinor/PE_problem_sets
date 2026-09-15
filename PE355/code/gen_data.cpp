#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    vector<ll> tc = {
        10,     // Co(10)=30
        20,     // small
        30,     // Co(30)=193
        50,     // medium
        100,    // Co(100)=1356
        200,    // medium-large
        500,    // large
        1000,   // larger
        5000,   // very large (greedy approx)
        200000  // PE355: Co(200000)=385291084
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; snprintf(fn, 32, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
