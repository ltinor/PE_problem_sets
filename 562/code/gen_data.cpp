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
    cases[0] = 5;  // sample
    for (int i = 1; i < 3; i++) cases[i] = rand_ll(1, 10);
    for (int i = 3; i < 6; i++) cases[i] = rand_ll(10, 100);
    cases[6] = 1;
    cases[7] = 100;
    for (int i = 8; i < 10; i++) cases[i] = rand_ll(50, 200);
    
    for (int i = 0; i < 10; i++) {
        string fn = "data/" + string(i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream f(fn);
        f << cases[i] << "\n";
        cout << "Generated " << fn << " r=" << cases[i] << "\n";
    }
    return 0;
}
