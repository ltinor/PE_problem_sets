#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    vector<ll> cases(10);
    cases[0] = 20; // S(20,7) = 49
    for (int i = 1; i < 4; i++) cases[i] = rand_ll(1, 100);
    for (int i = 4; i < 7; i++) cases[i] = rand_ll(1000, 100000);
    cases[7] = 1;
    cases[8] = 1000000; // S(1e6,2017) = 150850429
    cases[9] = 10000000;
    
    for (int i = 0; i < 10; i++) {
        string fn = "data/" + string(i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream f(fn);
        f << cases[i] << "\n";
        cout << "Generated " << fn << " N=" << cases[i] << "\n";
    }
    return 0;
}
