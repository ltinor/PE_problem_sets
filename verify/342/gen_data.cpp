#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    // PE answer: 5943040885644 for N = 10^10
    // For OJ, we use N ≤ 10^7 (feasible with sieve)
    
    vector<ll> cases(10);
    cases[0] = 100;          // small example
    cases[1] = 1000;         // small
    cases[2] = 10000;        // medium-small
    cases[3] = 50000;        // medium
    cases[4] = 100000;       // medium-large
    cases[5] = 500000;       // large
    cases[6] = 1000000;      // larger
    cases[7] = 2000000;      // even larger (different behavior)
    cases[8] = 5000000;      // near max
    cases[9] = 10000000;     // max for OJ
    
    for (int i = 0; i < 10; i++) {
        string fn = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream f(fn);
        f << cases[i] << "\n";
        f.close();
        cout << "Generated " << fn << " N=" << cases[i] << "\n";
    }
    return 0;
}
